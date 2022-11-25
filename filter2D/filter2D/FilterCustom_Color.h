#pragma once
#include "Header.h"
cv::Mat addpadding_color(cv::Mat& img, cv::Mat& kernel, int BorderType);
cv::Mat convolution_color(cv::Mat& img, cv::Mat& kernel);