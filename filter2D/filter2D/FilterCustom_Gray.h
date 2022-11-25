#pragma once
#include "Header.h"
cv::Mat addpadding_gray(cv::Mat& img, cv::Mat& kernel, int BorderType);
cv::Mat correlation_gray(cv::Mat& img, cv::Mat& kernel);