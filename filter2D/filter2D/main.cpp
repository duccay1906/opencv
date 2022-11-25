#include "Header.h"
int main()
{
    cv::Mat src; cv::Mat src_gray, opcv_img_gray, opcv_img_color, custom_img_gray, custom_img_color, padding_img_color, padding_img_gray;
    //Load input image
    src = cv::imread("src.png", cv::IMREAD_COLOR);
    cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
    cv::imwrite("source_gray.png", src_gray);
    cv::Mat kernel;
    //Selection the type of kernel
    int selection;
    std::cout << "Select the type of kernel:\n" << "1. Sobel X 3x3 \n2. Sobel Y 3x3 \n3. Laplace 3x3 \n4. Sobel X 5x5 \n5. Sobel Y 5x5 \n6. Averaging filter 5x5 \n" << std::endl;
    std::cin >> selection;
    switch (selection)
    {
    case 1:
    {
        //Sobel X 3x3
        kernel = (cv::Mat_<double>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
        break;
    }
    case 2:
    {
        //Sobel Y 3x3
        kernel = (cv::Mat_<double>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
        break;
    }
    case 3:
    {
        //Laplace 3x3
        kernel = (cv::Mat_<double>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
        break;
    }
    case 4:
    {
        //Sobel X 5x5
        kernel = (cv::Mat_<double>(5, 5) << 2, 2, 4, 2, 2, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, -1, -1, -2, -1, -1, -2, -2, -4, -2, -2);
        break;
    }
    case 5:
    {
        //Sobel Y 5x5
        kernel = (cv::Mat_<double>(5, 5) << 2, 1, 0, -1, -2, 2, 1, 0, -1, -2, 4, 2, 0, -2, -4, 2, 1, 0, -1, -2, 2, 1, 0, -1, -2);
        break;
    }
    case 6:
    {
        //Average Filter
        kernel = (cv::Mat_<double>(5, 5) << 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) / 25;
        break;
    }
    default:
        std::cout << "Invalid selection !" << std::endl;
        break;
    }
    //filter gray image
    {MEASURE_FUNCTION();
    padding_img_gray = addpadding_gray(src_gray, kernel, 2).clone();
    custom_img_gray = correlation_gray(padding_img_gray, kernel).clone();
    }
    cv::imshow("custom_gray_image", custom_img_gray);
    cv::imwrite("custom_gray_image.png", custom_img_gray);
    
    {MEASURE_FUNCTION();
    cv::filter2D(src_gray, opcv_img_gray, -1, kernel, cv::Point(-1, -1), 0.0, 2);
    }
    cv::imshow("opencv_gray_image", opcv_img_gray);
    cv::imwrite("opencv_gray_image.png", opcv_img_gray);
   
    //subtract image of opencv with image of custom
    cv::Mat subtr_gray;
    cv::absdiff(opcv_img_gray, custom_img_gray, subtr_gray);
    cv::imshow("subtract_gray", subtr_gray);
    cv::imwrite("subtract_gray.png", subtr_gray);
    //filter color image
    {MEASURE_FUNCTION();
    padding_img_color = addpadding_color(src, kernel, 2).clone();
    custom_img_color = correlation_color(padding_img_color, kernel).clone();
    }
    cv::imshow("custom_color_image", custom_img_color);
    cv::imwrite("custom_color_image.png", custom_img_color);
    {MEASURE_FUNCTION();
    cv::filter2D(src, opcv_img_color, -1, kernel, cv::Point(-1, -1), 0.0, 2);
    }
    cv::imshow("opencv_color_image", opcv_img_color);
    cv::imwrite("opencv_color_image.png", opcv_img_color);

    //Sobel function
    cv::Mat sobel_img;
    {MEASURE_FUNCTION();
    cv::Sobel(src, sobel_img, -1, 0, 1, 3, 1.0, 0.0, 2);
    }
    cv::imshow("Sobel_image", sobel_img);
    cv::imwrite("Sobel_image.png", sobel_img);

    //subtract sobel img and custom img
    cv::Mat subtract_sobel;
    cv::absdiff(sobel_img, custom_img_color, subtract_sobel);
    cv::imshow("Subtract_sobel", subtract_sobel);
    cv::imwrite("Subtract_sobel.png", subtract_sobel);
    //subtract image of opencv with image of custom
    cv::Mat subtr_color;
    cv::absdiff(opcv_img_color, custom_img_color, subtr_color);
    cv::imshow("subtract_color_image", subtr_color);
    cv::imwrite("subtract_color_image.png", subtr_color);
    cv::waitKey(0);
}