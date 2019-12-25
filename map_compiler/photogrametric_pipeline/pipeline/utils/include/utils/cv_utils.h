#ifndef __PIPELINE_UTILS_H__
#define __PIPELINE_UTILS_H__
#include <opencv2/opencv.hpp>
#include <string>
namespace NSFeatureExtraction {
    struct Utils {
        static cv::Mat convertToGreyScale(const cv::Mat &image);
        static cv::Mat loadImageFromFileName(const std::string &image_filename);
    };
} // namespace NSFeatureExtraction
#endif