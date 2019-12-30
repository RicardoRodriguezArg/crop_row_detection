#include "utils/cv_utils.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>


cv::Mat NSFeatureExtraction::Utils::convertToGreyScale(const cv::Mat &color_image) {
    cv::Mat grey_image;
    cv::cvtColor(color_image, grey_image, cv::COLOR_BGR2GRAY);
    return grey_image;
}

cv::Mat NSFeatureExtraction::Utils::loadImageFromFileName(const std::string &image_filename) {
    cv::Mat result_image;
    if (!image_filename.empty()) {
        result_image = cv::imread(image_filename, cv::IMREAD_COLOR);
    }
    return result_image;
}