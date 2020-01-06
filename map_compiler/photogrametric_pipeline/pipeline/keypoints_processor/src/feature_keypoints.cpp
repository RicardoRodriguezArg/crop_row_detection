#include "keypoints_processor/feature_keypoints.h"
#include "keypoints_processor/feature_exceptions.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "utils/cv_utils.h"
#include <algorithm>
#include <exception>

NSFeatureExtraction::FeatureExtraction::FeatureExtraction(
    const int max_features = 500, const float match_percent_aceptable = 0.15f,
    const std::string &descriptor_name = "FlannBased")
    : max_features_(max_features), orb_detector_(cv::ORB::create(max_features)),
      match_percent_aceptable_(match_percent_aceptable),
      current_state_(FEATURE_CONSTANTS::KEYPROCESS_INFO::NOT_PROCESSED) {
    // TODO: Check at compile time string is not empty
    if (!descriptor_name.empty()) {

        matcher_ = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    }
}

void NSFeatureExtraction::FeatureExtraction::checkPreliminars() {
    checkImageIsNotEmpty();
    checkMatcherIsSet();
}

void NSFeatureExtraction::FeatureExtraction::detectFeatures() {
    current_state_ = FEATURE_CONSTANTS::KEYPROCESS_INFO::ERROR;
    checkPreliminars();
    const auto &&image_in_grey_scale = NSFeatureExtraction::Utils::convertToGreyScale(image_);
    orb_detector_->detectAndCompute(image_in_grey_scale, cv::Mat(), keyPoints_, descriptor_);
    current_state_ = FEATURE_CONSTANTS::KEYPROCESS_INFO::OK;
}

const std::vector<cv::KeyPoint>
NSFeatureExtraction::FeatureExtraction::getKeyPointContainer() const {
    return keyPoints_;
}

cv::Mat NSFeatureExtraction::FeatureExtraction::getKeyPointDescriptor() const {
    return descriptor_;
}

cv::Mat NSFeatureExtraction::FeatureExtraction::getKeyPointDescriptor() { return descriptor_; }

void NSFeatureExtraction::FeatureExtraction::checkImageIsNotEmpty() {
    if (image_.empty()) {
        std::string errorMessage = std::string("Error: Empty Raw Image Mat");
        throw std::runtime_error(errorMessage);
    }
}

void NSFeatureExtraction::FeatureExtraction::checkMatcherIsSet() {

    if (image_.empty()) {
        std::string errorMessage = std::string("Error: Matcher not Init or not define");
        throw FeatureException(errorMessage);
    }
}

void NSFeatureExtraction::FeatureExtraction::setRawImage(const cv::Mat &raw_image) {
    image_ = raw_image;
}

std::vector<std::optional<cv::DMatch>>
NSFeatureExtraction::FeatureExtraction::match(const cv::Mat other_descriptor) {
    std::vector<std::vector<cv::DMatch>> knn_matches{};
    std::vector<std::optional<cv::DMatch>> result{};
    matcher_->knnMatch(descriptor_, other_descriptor, knn_matches, KNN_BEST_MATCHED_VALUE);

    auto select_match_by_threshold = [&](const std::vector<cv::DMatch> &raw_matched) {
        std::optional<cv::DMatch> result{};
        if (!raw_matched.empty()) {
            if (raw_matched[0].distance < MATCH_RATIO_THRESHOLD * raw_matched[1].distance) {
                return std::make_optional<cv::DMatch>(raw_matched[0]);
            }
        }
        return result;
    };
    // TODO: Implement emplace_inserter
    std::transform(std::begin(knn_matches), std::end(knn_matches), std::back_inserter(result),
                   select_match_by_threshold);

    return result;
}

cv::Mat NSFeatureExtraction::FeatureExtraction::FindFundamentalMatrix(
    const std::vector<std::optional<cv::DMatch>> &matches_keypoint,
    const std::vector<cv::KeyPoint> &other_keypoint) const {
    std::vector<std::tuple<cv::Point2f, cv::Point2f>> points_repository;
    const auto point_selector_functor =
        [&, other_keypoint, points_repository](const std::optional<cv::DMatch> &match) {
            const auto &current_descriptor_index = keyPoints_[(*match).queryIdx].pt;
            const auto &other_descriptor_index = other_keypoint[(*match).queryIdx].pt;
            return std::make_tuple(current_descriptor_index, other_descriptor_index);
        };

    std::transform(std::begin(matches_keypoint), std::end(matches_keypoint),
                   std::back_inserter(points_repository), point_selector_functor);
    const auto transformer_first = [](const std::tuple<cv::Point2f, cv::Point2f> &tuple) {
        return std::get<0>(tuple);
    };

    const auto transformer_second = [](const std::tuple<cv::Point2f, cv::Point2f> &tuple) {
        return std::get<1>(tuple);
    };
    std::vector<cv::Point2f> source_points;
    std::vector<cv::Point2f> target_points;
    std::transform(std::begin(points_repository), std::end(points_repository),
                   std::back_inserter(source_points), transformer_first);

    std::transform(std::begin(points_repository), std::end(points_repository),
                   std::back_inserter(source_points), transformer_second);
    cv::Mat mask;
    cv::findFundamentalMat(source_points, target_points, cv::FM_RANSAC, 3.0, 0.99, mask);
    return mask;
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

FEATURE_CONSTANTS::KEYPROCESS_INFO NSFeatureExtraction::FeatureExtraction::currentState() const {
    return current_state_;
}
