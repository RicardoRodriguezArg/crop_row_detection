#ifndef __KEYPOINT_LANDMARK_H__
#define __KEYPOINT_LANDMARK_H__
#include <opencv2/opencv.hpp>
namespace NSFeatureExtraction {
    struct LandMark {
        cv::Point3f point_;
        int seen_in_many_cameras_ = {0};
    };
} // namespace NSFeatureExtraction
#endif