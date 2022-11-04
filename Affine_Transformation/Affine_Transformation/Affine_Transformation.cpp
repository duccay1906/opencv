#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
void showHistogram(cv::Mat& img)
{
	int bins = 256;             // number of bins
	int nc = img.channels();    // number of channels

	std::vector<cv::Mat> hist(nc);       // histogram arrays

	// Initalize histogram arrays
	for (int i = 0; i < hist.size(); i++)
		hist[i] = cv::Mat::zeros(1, bins, CV_32SC1);

	// Calculate the histogram of the image
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			for (int k = 0; k < nc; k++)
			{
				uchar val = nc == 1 ? img.at<uchar>(i, j) : img.at<cv::Vec3b>(i, j)[k];
				hist[k].at<int>(val) += 1;
			}
		}
	}

	// For each histogram arrays, obtain the maximum (peak) value
	// Needed to normalize the display later
	int hmax[3] = { 0,0,0 };
	for (int i = 0; i < nc; i++)
	{
		for (int j = 0; j < bins - 1; j++)
			hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
	}

	const char* wname[3] = { "blue", "green", "red" };
	cv::Scalar colors[3] = { cv::Scalar(255,0,0), cv::Scalar(0,255,0), cv::Scalar(0,0,255) };

	std::vector<cv::Mat> canvas(nc);

	// Display each histogram in a canvas
	for (int i = 0; i < nc; i++)
	{
		canvas[i] = cv::Mat::ones(125, bins, CV_8UC3);

		for (int j = 0, rows = canvas[i].rows; j < bins - 1; j++)
		{
			line(
				canvas[i],
				cv::Point(j, rows),
				cv::Point(j, rows - (hist[i].at<int>(j) * rows / hmax[i])),
				nc == 1 ? cv::Scalar(200, 200, 200) : colors[i],
				1, 8, 0
			);
		}

		imshow(nc == 1 ? "value" : wname[i], canvas[i]);
	}
}
int main()
{
	cv::Mat src = cv::imread("car.jpg");

	cv::Point2f srcTri[3];
	srcTri[0] = cv::Point2f(0.f, 0.f);
	srcTri[1] = cv::Point2f(src.cols - 1.f, 0.f);
	srcTri[2] = cv::Point2f(0.f, src.rows - 1.f);

	cv::Point2f dstTri[3];
	dstTri[0] = cv::Point2f(0.f, src.rows * 0.33f);
	dstTri[1] = cv::Point2f(src.cols * 0.85f, src.rows * 0.25f);
	dstTri[2] = cv::Point2f(src.cols * 0.15f, src.rows * 0.7f);

	cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
	cv::Mat warp_dst = cv::Mat::zeros(src.rows, src.cols, src.type());

	cv::warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	cv::Point center = cv::Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -30;
	double scale = 0.7;

	cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, scale);

	cv::Mat warp_rotate_dst;
	cv::warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());

	cv::imshow("source", src);
	cv::imshow("Warp", warp_dst);
	cv::imshow("Warp+Rotate", warp_rotate_dst);

	cv::Mat img = cv::imread("low.png");
	cv::Mat img_gray, dst;
	cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	cv::equalizeHist(img_gray, dst);
	showHistogram(dst);

	// show result
	cv::imshow("source_image", img);
	cv::imshow("destination_image", dst);
	cv::waitKey(0);
	return 0;
}