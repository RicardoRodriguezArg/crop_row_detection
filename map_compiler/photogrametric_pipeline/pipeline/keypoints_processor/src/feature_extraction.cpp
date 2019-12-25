#include "keypoints_processor/feature_extraction.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "utils/cv_utils.h"

#include <algorithm>

NSFeatureExtraction::FeatureExtraction::FeatureExtraction(
    const int max_features = 500, const float match_percent_aceptable = 0.15f,
    const std::string &descriptor_name = "FlannBased")
    : max_features_(max_features), orb_detector_(cv::ORB::create(max_features)),
      matcher_(cv::DescriptorMatcher::create(descriptor_name)),
      match_percent_aceptable_(match_percent_aceptable) {}

void NSFeatureExtraction::FeatureExtraction::detectFeatures() {
    const auto &&image_in_grey_scale = NSFeatureExtraction::Utils::convertToGreyScale(image_);
    orb_detector_->detectAndCompute(image_in_grey_scale, cv::Mat(), keyPoints_, descriptor_);
}

void NSFeatureExtraction::FeatureExtraction::setRawImage(const cv::Mat &raw_image) {
    image_ = raw_image;
}

std::vector<cv::DMatch> NSFeatureExtraction::FeatureExtraction::match(cv::Mat other_descriptor) {
    std::vector<cv::DMatch> result_matches{};
    matcher_->match(descriptor_, other_descriptor, result_matches, cv::Mat());
    // Sort matches by score

    std::sort(result_matches.begin(), result_matches.end());
    // Remove not so good matches
    const auto numGoodMatches = result_matches.size() * match_percent_aceptable_;
    result_matches.erase(result_matches.begin() + numGoodMatches, result_matches.end());
    return result_matches;
}

cv::Mat NSFeatureExtraction::FeatureExtraction::createPerpestiveMatrix(
    const std::vector<cv::DMatch> &matches, const std::vector<cv::KeyPoint> &keyPoints) const {
    std::vector<cv::Point2f> points1, points2;
    for (size_t i = 0; i < matches.size(); i++) {
        points1.push_back(keyPoints[matches[i].queryIdx].pt);
        points2.push_back(keyPoints[matches[i].trainIdx].pt);
    }
    return cv::findHomography(points1, points2, cv::RANSAC);
}

cv::Mat NSFeatureExtraction::FeatureExtraction::createFundamentalMatrix(
    const std::vector<cv::DMatch> &matches, const std::vector<cv::KeyPoint> &keyPoints) const {
    std::vector<cv::Point2f> points1, points2;
    std::vector<uchar> mask;
    for (size_t i = 0; i < matches.size(); i++) {
        points1.push_back(keyPoints[matches[i].queryIdx].pt);
        points2.push_back(keyPoints[matches[i].trainIdx].pt);
    }
    return cv::findFundamentalMat(points1, points2, cv::FM_RANSAC, 3.0, 0.99, mask);
}

NSFeatureExtraction::FeatureExtraction::KeyPointId
NSFeatureExtraction::FeatureExtraction::getKeyPointID() const {
    return keypoint_id_;
}

void NSFeatureExtraction::FeatureExtraction::setKeyPointId(
    const std::string &image_filename,
    const NSFeatureExtraction::FeatureExtraction::KeyPoint &local_keypoint) {
    keypoint_id_ = std::make_pair(local_keypoint, std::hash<std::string>{}(image_filename));
}

void NSFeatureExtraction::FeatureExtraction::addExternalReference(
    const KeyPointId external_keypoint_id) {
    // matched_external_keypoints_.insert(external_keypoint_id);
}
