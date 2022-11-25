#include "HistogramFunction.h"
void imhist(cv::Mat& image, int histogram[256])
{
    for (int i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }
    for (int x = 0; x < image.cols; x++)
    {
        for (int y = 0; y < image.rows; y++)
        {
            histogram[(int)image.at<uchar>(y, x)]++;
        }
    }
}

int maxhist(int histogram[256])
{
    int max = histogram[0];
    for (int i = 0; i < 256; i++)
    {
        if (max <= histogram[i])
        {
            max = histogram[i];
        }
    }
    return max;
}
void histDisplay(int histogram[256], const char* name)
{
    int hist[256];
    for (int i = 0; i < 256; i++)
    {
        hist[i] = histogram[i];
    }
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / 256);

    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(255, 255, 255));
    //normalize
    for (int i = 0; i < 256; i++)
    {
        hist[i] = ((double)hist[i] / maxhist(histogram)) * histImage.rows;
    }
    //draw the histogram
    for (int i = 0; i < 256; i++)
    {
        line(histImage, cv::Point(bin_w * i, hist_h), cv::Point(bin_w * i, hist_h - hist[i]), cv::Scalar(0, 0, 0), 1, 8, 0);
    }
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    //draw linear line

    imshow(name, histImage);
    std::string text = (std::string)name + ".png";
    cv::imwrite(text, histImage);
}