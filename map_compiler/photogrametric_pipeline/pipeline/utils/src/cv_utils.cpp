#include "utils/cv_utils.h"

cv::Mat NSFeatureExtraction::Utils::convertToGreyScale(const cv::Mat &image) {
    cv::Mat result_image;
    cv::cvtColor(image, result_image, cv::COLOR_BGR2GRAY);
    return result_image;
}