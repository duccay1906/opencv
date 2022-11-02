#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

int main()
{
    // Declare the output variables
    cv::Mat img, edge_detected, edge_detectedP;
    // Load an image 
    img = cv::imread("z.png");
    // Copy source image
    cv::Mat imgP = img.clone();
    cv::cvtColor(img, edge_detected, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(edge_detected, edge_detected, cv::Size(3, 3), 0, 0, 4);
    // Edge detection
    cv::Canny(edge_detected, edge_detected, 50, 150);
    cv::imshow("edge_detected", edge_detected);
    // Standard Hough Line Transform
    std::vector<cv::Vec2f> Lines;
    cv::HoughLines(edge_detected, Lines, 1, CV_PI / 180, 100, 0, 0);
    for (size_t i = 0; i < Lines.size(); i++)
    {
        float rho = Lines[i][0], theta = Lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        cv::line(img, pt1, pt2, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
    }
    cv::imshow("Result_image", img);

    // Probabilistic Line Transform
    cv::cvtColor(imgP, edge_detectedP, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(edge_detectedP, edge_detectedP, cv::Size(3, 3), 0, 0, 4);
    cv::Canny(edge_detectedP, edge_detectedP, 50, 150);
    cv::imshow("edge_detected_P", edge_detectedP);
    std::vector<cv::Vec4i> LinesP;
    cv::HoughLinesP(edge_detectedP, LinesP, 1, CV_PI / 180, 50, 30, 10);
    for (size_t i = 0; i < Lines.size(); i++)
    {
        cv::Vec4i l = LinesP[i];
        line(imgP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }
    cv::imshow("Result_imageP", imgP);

    // Hough Circle
    cv::Mat src = cv::imread("test.png");
    cv::resize(src, src, cv::Size(680, 480));
    cv::Mat dst_gray, dst_blur, dst_canny;
    cv::cvtColor(src, dst_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(dst_gray, dst_blur, cv::Size(9, 9), 0);
    cv::Canny(dst_gray, dst_canny, 50, 200);
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(dst_canny, circles, cv::HOUGH_GRADIENT, 1, 30, 200, 10, 15, 30);
    for (size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(src, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        circle(src, center, radius, cv::Scalar(221, 150, 249), 2, 8, 0);
    }
    cv::imshow("Canny", dst_canny);
    cv::imshow("Result_HoughCircle", src);
    cv::waitKey(0);
    return 0;
}