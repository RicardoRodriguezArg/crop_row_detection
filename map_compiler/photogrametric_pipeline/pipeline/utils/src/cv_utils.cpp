#include "utils/cv_utils.h"
#include <iostream>

cv::Mat NSFeatureExtraction::Utils::convertToGreyScale(const cv::Mat &image) {
    cv::Mat result_image;
    cv::cvtColor(image, result_image, cv::COLOR_BGR2GRAY);
    return result_image;
}

cv::Mat NSFeatureExtraction::Utils::loadImageFromFileName(const std::string &image_filename) {
    cv::Mat result_image;

    if (!image_filename.empty()) {

        result_image = cv::imread(image_filename);
        std::cout << "result_image Empty: " << std::boolalpha << result_image.empty() << std::endl;
    }
    return result_image;
}