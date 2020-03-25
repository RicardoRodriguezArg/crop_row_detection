#include "utils/cv_utils.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace NSFeatureExtraction {
    cv::Mat Utils::convertToGreyScale(const cv::Mat &color_image) {
        cv::Mat grey_image;
        cv::cvtColor(color_image, grey_image, cv::COLOR_BGR2GRAY);
        return grey_image;
    }

    cv::Mat Utils::loadImageFromFileName(const std::string &image_filename) {
        cv::Mat result_image;
        if (!image_filename.empty()) {
            std::cout << "image not empty" << std::endl;
            result_image = cv::imread(image_filename, cv::IMREAD_COLOR);
        }
        return result_image;
    }

    std::tuple<double, double> Utils::getImageDimension(const std::string &image_filename) {
        const auto &image = Utils::loadImageFromFileName(image_filename);
        return {image.size().width, image.size().height};
    }

} // namespace NSFeatureExtraction