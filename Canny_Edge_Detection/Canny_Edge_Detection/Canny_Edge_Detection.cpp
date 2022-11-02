#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat img, edge_detecing;
int thresh_low = 0;
int thresh_high = 300;
void Canny_Edge(int, void*)
{
    cv::GaussianBlur(img, edge_detecing, cv::Size(3, 3), 0, 0, 4);
    cv::Canny(edge_detecing, edge_detecing, thresh_low, thresh_high);
    cv::imshow("Canny_image", edge_detecing);
}

int main()
{
    img = cv::imread("sobel.png", 0);
    cv::namedWindow("Canny_image", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("thresh_low", "Canny_image", &thresh_low, thresh_high, Canny_Edge);
    cv::createTrackbar("thresh_high", "Canny_image", &thresh_high, thresh_high, Canny_Edge);
    Canny_Edge(0, 0);
    cv::waitKey(0);
}
