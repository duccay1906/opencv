#include "FilterCustom_Color.h"

cv::Mat addpadding_color(cv::Mat& img, cv::Mat& kernel, int BorderType)
{
    cv::Mat img_padding(img.rows + kernel.rows - 1, img.cols + kernel.cols - 1, img.type());
    for (int x = 0; x < img.rows; x++)
    {
        for (int y = 0; y < img.cols; y++)
        {
            img_padding.at<cv::Vec3b>(x + (kernel.rows - 1) / 2, y + (kernel.cols - 1) / 2)[0] = img.at<cv::Vec3b>(x, y)[0];
            img_padding.at<cv::Vec3b>(x + (kernel.rows - 1) / 2, y + (kernel.cols - 1) / 2)[1] = img.at<cv::Vec3b>(x, y)[1];
            img_padding.at<cv::Vec3b>(x + (kernel.rows - 1) / 2, y + (kernel.cols - 1) / 2)[2] = img.at<cv::Vec3b>(x, y)[2];
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
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(x, (kernel.cols - 1) / 2)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(x, (kernel.cols - 1) / 2)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(x, (kernel.cols - 1) / 2)[2];

                img_padding.at<cv::Vec3b>(x, img_padding.cols - (y + 1))[0] = img_padding.at<cv::Vec3b>(x, img_padding.cols - ((kernel.cols - 1) / 2 + 1))[0];
                img_padding.at<cv::Vec3b>(x, img_padding.cols - (y + 1))[1] = img_padding.at<cv::Vec3b>(x, img_padding.cols - ((kernel.cols - 1) / 2 + 1))[1];
                img_padding.at<cv::Vec3b>(x, img_padding.cols - (y + 1))[2] = img_padding.at<cv::Vec3b>(x, img_padding.cols - ((kernel.cols - 1) / 2 + 1))[2];
            }
        }
        for (int y = 0; y < img_padding.cols; y++)
        {
            for (int x = 0; x < (kernel.rows - 1) / 2; x++)
            {
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>((kernel.rows - 1) / 2, y)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>((kernel.rows - 1) / 2, y)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>((kernel.rows - 1) / 2, y)[2];

                img_padding.at<cv::Vec3b>(img_padding.rows - (x + 1), y)[0] = img_padding.at<cv::Vec3b>(img_padding.rows - ((kernel.rows - 1) / 2 + 1), y)[0];
                img_padding.at<cv::Vec3b>(img_padding.rows - (x + 1), y)[1] = img_padding.at<cv::Vec3b>(img_padding.rows - ((kernel.rows - 1) / 2 + 1), y)[1];
                img_padding.at<cv::Vec3b>(img_padding.rows - (x + 1), y)[2] = img_padding.at<cv::Vec3b>(img_padding.rows - ((kernel.rows - 1) / 2 + 1), y)[2];
            }
        }
        break;
    }
    case 2://BorderType Reflect
    {
        for (int x = 0; x < img_padding.rows; x++)
        {
            int i = (kernel.cols - 1) / 2;
            for (int y = (kernel.cols - 1) / 2 - 1; y >= 0; y--)
            {
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(x, i)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(x, i)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(x, i)[2];
                i++;
            }
            int j = img_padding.cols - (kernel.cols - 1) / 2 - 1;
            for (int y = img_padding.cols - (kernel.cols - 1) / 2; y < img_padding.cols; y++)
            {
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(x, j)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(x, j)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(x, j)[2];
                j--;
            }
        }
        for (int y = 0; y < img_padding.cols; y++)
        {
            int i = (kernel.rows - 1) / 2;
            for (int x = (kernel.rows - 1) / 2 - 1; x >= 0; x--)
            {
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(i, y)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(i, y)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(i, y)[2];
                i++;
            }
            int j = img_padding.rows - (kernel.rows - 1) / 2 - 1;
            for (int x = img_padding.rows - (kernel.rows - 1) / 2; x < img_padding.rows; x++)
            {
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(j, y)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(j, y)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(j, y)[2];
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
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(x, j)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(x, j)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(x, j)[2];
                j--;
            }
            int i = (kernel.cols - 1) / 2;
            for (int y = img_padding.cols - (kernel.cols - 1) / 2; y < img_padding.cols; y++)
            {
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(x, i)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(x, i)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(x, i)[2];
                i++;
            }
        }
        for (int y = 0; y < img_padding.cols; y++)
        {
            int i = img_padding.rows - (kernel.rows - 1) / 2 - 1;
            for (int x = (kernel.rows - 1) / 2 - 1; x >= 0; x--)
            {
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(i, y)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(i, y)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(i, y)[2];
                i--;
            }
            int j = (kernel.rows - 1) / 2;
            for (int x = img_padding.rows - (kernel.rows - 1) / 2; x < img_padding.rows; x++)
            {
                img_padding.at<cv::Vec3b>(x, y)[0] = img_padding.at<cv::Vec3b>(j, y)[0];
                img_padding.at<cv::Vec3b>(x, y)[1] = img_padding.at<cv::Vec3b>(j, y)[1];
                img_padding.at<cv::Vec3b>(x, y)[2] = img_padding.at<cv::Vec3b>(j, y)[2];
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
cv::Mat correlation_color(cv::Mat& img, cv::Mat& kernel)
{
    cv::Mat conv_img(img.rows - (kernel.rows - 1), img.cols - (kernel.cols - 1), img.type());
    for (int x = (kernel.rows - 1) / 2; x < img.rows - (kernel.rows - 1) / 2; x++)
    {
        for (int y = (kernel.cols - 1) / 2; y < img.cols - (kernel.cols - 1) / 2; y++)
        {
            double temp[3] = { 0 };
            for (int i = -(kernel.rows - 1) / 2; i <= (kernel.rows - 1) / 2; i++)
            {
                for (int j = -(kernel.cols - 1) / 2; j <= (kernel.cols - 1) / 2; j++)
                {
                    temp[0] = temp[0] + img.at<cv::Vec3b>(x + i, y + j)[0] * kernel.at<double>(i + (kernel.rows - 1) / 2, j + (kernel.cols - 1) / 2);
                    temp[1] = temp[1] + img.at<cv::Vec3b>(x + i, y + j)[1] * kernel.at<double>(i + (kernel.rows - 1) / 2, j + (kernel.cols - 1) / 2);
                    temp[2] = temp[2] + img.at<cv::Vec3b>(x + i, y + j)[2] * kernel.at<double>(i + (kernel.rows - 1) / 2, j + (kernel.cols - 1) / 2);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if (temp[i] < 0)
                {
                    temp[i] = 0;
                }
                else if (temp[i] > 255)
                {
                    temp[i] = 255;
                }
            }
            conv_img.at<cv::Vec3b>(x - (kernel.rows - 1) / 2, y - (kernel.rows - 1) / 2)[0] = temp[0];
            conv_img.at<cv::Vec3b>(x - (kernel.rows - 1) / 2, y - (kernel.rows - 1) / 2)[1] = temp[1];
            conv_img.at<cv::Vec3b>(x - (kernel.rows - 1) / 2, y - (kernel.rows - 1) / 2)[2] = temp[2];
        }
    }
    return conv_img;
}
