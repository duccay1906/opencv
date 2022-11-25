#pragma once
#include "Header.h"
void imhist(cv::Mat& image, int histogram[256]);
int maxhist(int histogram[256]);
void histDisplay(int histogram[256], const char* name);

