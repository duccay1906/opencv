#include <iostream>
#include <sstream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
int g = 0;
cv::Mat src, gammaImg;
// function gamma Correction
void gammaCorrection(cv::Mat& src, cv::Mat& dst, int gamma)
{
    float invgamma = 1.f / ((float)gamma * 0.2f);
    cv::Mat table(1, 256, CV_8U);
    uchar* p = table.ptr();
    for (int i = 0; i < 256; i++)
    {
        p[i] = (uchar)(pow(i / 255.0, invgamma) * 255);
    }
    cv::LUT(src, table, dst);
}

// function put text value of gamma in image
void Put_G(cv::Mat& src, int gamma)
{
    std::stringstream name;
    name.precision(4);
    name << (float)gamma * 0.2f;
    std::string text = "gamma = " + name.str();
    cv::putText(src, text, cv::Point(20, 30), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
}
// function callBackTrackbar
void Gamma_Trans(int, void*)
{
    gammaCorrection(src, gammaImg, g);
    Put_G(gammaImg, g);
    cv::imshow("Destination", gammaImg);
}
int main()
{
    // Load input image
    src = cv::imread("src.jpg");
    cv::namedWindow("Destination", cv::WINDOW_AUTOSIZE);
    // create a Trackbar with gamma value
    cv::createTrackbar("g", "Destination", &g, 10, Gamma_Trans);
    cv::waitKey(0);
}


