#include "utils/cv_utils.h"
#include <opencv2/imgcodecs.hpp>

#include <limits.h>
#include <stdio.h>
#include <unistd.h>

cv::Mat NSFeatureExtraction::Utils::convertToGreyScale(const cv::Mat &image) {
    cv::Mat result_image;
    cv::cvtColor(image, result_image, cv::COLOR_BGR2GRAY);
    return result_image;
}

cv::Mat NSFeatureExtraction::Utils::loadImageFromFileName(const std::string &image_filename) {
    cv::Mat result_image;

    if (!image_filename.empty()) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current working dir: %s\n", cwd);
        }
        result_image = cv::imread(image_filename, cv::IMREAD_COLOR);
        std::cout << "result_image Empty: " << std::boolalpha << result_image.empty() << std::endl;
    }
    return result_image;
}