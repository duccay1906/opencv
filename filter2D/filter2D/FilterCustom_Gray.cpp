#include "FilterCustom_Gray.h"
cv::Mat addpadding_gray(cv::Mat& img, cv::Mat&  kernel, int BorderType)
{
    cv::Mat img_padding = cv::Mat::zeros(img.rows + kernel.rows - 1, img.cols + kernel.cols - 1, img.type());
    for (int x = 0; x < img.rows; x++)
    {
        for (int y = 0; y < img.cols; y++)
        {
            img_padding.at<uchar>(x + (kernel.rows - 1) / 2, y + (kernel.cols - 1) / 2) = img.at<uchar>(x, y);
        }
    }
    switch (BorderType)
    {
    case 1://BorderType Replicate
    {
        for (int x = 0; x < img_padding.rows; x++)
        {
            for (int y = 0; y < (kernel.cols - 1) / 2; y++)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(x, (kernel.cols - 1) / 2);
                img_padding.at<uchar>(x, img_padding.cols - (y + 1)) = img_padding.at<uchar>(x, img_padding.cols - ((kernel.cols - 1) / 2 + 1));
            }
        }
        for (int y = 0; y < img_padding.cols; y++)
        {
            for (int x = 0; x < (kernel.rows - 1) / 2; x++)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>((kernel.rows - 1) / 2, y);
                img_padding.at<uchar>(img_padding.rows - (x + 1), y) = img_padding.at<uchar>(img_padding.rows - ((kernel.rows - 1) / 2 + 1), y);
            }
        }
        break;
    }
    case 2://BorderType Reflect
    {
        for (int x = 0; x < img_padding.rows; x++)
        {
            int i = (kernel.cols - 1) / 2;
            for (int y = (kernel.cols - 1) / 2 - 1;  y >= 0;  y--)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(x, i);
                i++;
            }
            int j = img_padding.cols - (kernel.cols - 1) / 2 - 1;
            for (int y = img_padding.cols - (kernel.cols - 1) / 2; y < img_padding.cols; y++)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(x, j);
                j--;
            }
        }
        for (int y = 0; y < img_padding.cols; y++)
        {
            int i = (kernel.rows - 1) / 2;
            for (int x = (kernel.rows - 1) / 2 - 1; x >= 0; x--)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(i, y);
                i++;
            }
            int j = img_padding.rows - (kernel.rows - 1) / 2 - 1;
            for (int x = img_padding.rows - (kernel.rows - 1) / 2; x < img_padding.rows; x++)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(j, y);
                j--;
            }
        }
        break;
    }
    case 3://BorderType Wrap
    {
        for (int x = 0; x < img_padding.rows; x++)
        {
            int j = img_padding.cols - (kernel.cols - 1) / 2 - 1;
            for (int y = (kernel.cols - 1) / 2 - 1; y >= 0; y--)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(x, j);
                j--;
            }
            int i = (kernel.cols - 1) / 2;
            for (int y = img_padding.cols - (kernel.cols - 1) / 2; y < img_padding.cols; y++)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(x, i);
                i++;
            }
        }
        for (int y = 0; y < img_padding.cols; y++)
        {
            int i = img_padding.rows - (kernel.rows - 1) / 2 - 1;
            for (int x = (kernel.rows - 1) / 2 - 1; x >= 0; x--)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(i, y);
                i--;
            }
            int j = (kernel.rows - 1) / 2;
            for (int x = img_padding.rows - (kernel.rows - 1) / 2; x < img_padding.rows; x++)
            {
                img_padding.at<uchar>(x, y) = img_padding.at<uchar>(j, y);
                j++;
            }
        }
        break;
    }
    default:
        break;
    }
    return img_padding;
}
cv::Mat correlation_gray(cv::Mat& img, cv::Mat& kernel)
{
    cv::Mat dst(img.rows - (kernel.rows - 1), img.cols - (kernel.cols - 1), img.type());
    for (int x = (kernel.rows - 1) / 2; x < img.rows - (kernel.rows - 1) / 2; x++)
    {
        for (int y = (kernel.cols - 1) / 2; y < img.cols - (kernel.cols - 1) / 2; y++)
        {
            int temp = 0;
            for (int i = -(kernel.rows - 1) / 2; i <= (kernel.rows - 1) / 2; i++)
            {
                for (int j = -(kernel.cols - 1) / 2; j <= (kernel.cols - 1) / 2; j++)
                {
                    temp = temp + img.at<uchar>(x + i, y + j) * kernel.at<double>(i + (kernel.rows - 1) / 2, j + (kernel.cols - 1) / 2);
                }
            }
            if (temp < 0)
            {
                dst.at<uchar>(x - (kernel.rows - 1) / 2, y - (kernel.rows - 1) / 2) = (uchar)0;
            }
            else if (temp > 255)
            {
                dst.at<uchar>(x - (kernel.rows - 1) / 2, y - (kernel.rows - 1) / 2) = (uchar)255;
            }
            else
            {
                dst.at<uchar>(x - (kernel.rows - 1) / 2, y - (kernel.rows - 1) / 2) = (uchar)temp;
            }
        }
    }
    return dst;
}