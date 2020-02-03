#include "keypoints_processor/feature_keypoints.h"
#include "keypoints_processor/feature_exceptions.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "utils/cv_utils.h"
#include <algorithm>
#include <exception>

namespace NSFeatureExtraction {
    FeatureExtraction::FeatureExtraction(const int max_features = 500,
                                         const float match_percent_aceptable = 0.15f,
                                         const std::string &descriptor_name = "FlannBased")
        : max_features_(max_features), orb_detector_(cv::ORB::create(max_features)),
          match_percent_aceptable_(match_percent_aceptable),
          current_state_(FEATURE_CONSTANTS::KEYPROCESS_INFO::NOT_PROCESSED) {
        // TODO: Check at compile time string is not empty
        if (!descriptor_name.empty()) {

            matcher_ = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
        }
    }

    void FeatureExtraction::checkPreliminars() {
        checkImageIsNotEmpty();
        checkMatcherIsSet();
    }

    void FeatureExtraction::detectFeatures() {
        current_state_ = FEATURE_CONSTANTS::KEYPROCESS_INFO::ERROR;
        checkPreliminars();
        const auto &&image_in_grey_scale = Utils::convertToGreyScale(image_);
        orb_detector_->detectAndCompute(image_in_grey_scale, cv::Mat(), keyPoints_, descriptor_);
        current_state_ = FEATURE_CONSTANTS::KEYPROCESS_INFO::OK;
    }

    const std::vector<cv::KeyPoint> FeatureExtraction::getKeyPointContainer() const {
        return keyPoints_;
    }

    cv::Mat FeatureExtraction::getKeyPointDescriptor() const { return descriptor_; }

    void FeatureExtraction::checkImageIsNotEmpty() {
        if (image_.empty()) {
            std::string errorMessage = std::string("Error: Empty Raw Image Mat");
            throw std::runtime_error(errorMessage);
        }
    }

    void FeatureExtraction::checkMatcherIsSet() {

        if (image_.empty()) {
            std::string errorMessage = std::string("Error: Matcher not Init or not define");
            throw FeatureException(errorMessage);
        }
    }

    void FeatureExtraction::setRawImage(const cv::Mat &raw_image) { image_ = raw_image; }

    cv::Mat FeatureExtraction::getDescriptor() const { return descriptor_; }

    std::vector<cv::KeyPoint> FeatureExtraction::getKeyPoints() const { return keyPoints_; }

    void FeatureExtraction::match(const FeatureExtraction::KeyPointInfoUnit &other_kp_data) {
        std::vector<std::vector<cv::DMatch>> knn_matches{};

        matcher_->knnMatch(descriptor_, std::get<2>(other_kp_data), knn_matches,
                           KNN_BEST_MATCHED_VALUE);

        const auto filter_matches_index_mask = FilterMatches(knn_matches);
        SetExternalKeyPoints(std::get<0>(other_kp_data), filter_matches_index_mask);
    }

    std::vector<cv::DMatch> FeatureExtraction::FilterMatches(
        const std::vector<std::vector<cv::DMatch>> &matched_keypoints) const {

        std::vector<cv::DMatch> mask;
        const auto &select_match_by_threshold = [this, &mask](const auto &match) {
            if (match[0].distance < MATCH_RATIO_THRESHOLD * match[1].distance) {
                mask.push_back(match[0]);
            }
        };

        std::for_each(std::begin(matched_keypoints), std::end(matched_keypoints),
                      select_match_by_threshold);
        // cv::findFundamentalMat(source, target, cv::FM_RANSAC, 3.0, 0.99, mask);
        return mask;
    }

    FeatureExtraction::KeyPointId FeatureExtraction::getId() const { return keypoint_id_; }

    void FeatureExtraction::setKeyPointId(const FeatureExtraction::KeyPointId &image_id) noexcept {
        keypoint_id_ = image_id;
    }

    FEATURE_CONSTANTS::KEYPROCESS_INFO FeatureExtraction::currentState() const {
        return current_state_;
    }

    FeatureExtraction::KeyPointInfoUnit FeatureExtraction::getKeyPointInfoUnit() const {
        return {keypoint_id_, keyPoints_, descriptor_};
    }

    void FeatureExtraction::SetExternalKeyPoints(const FeatureExtraction::KeyPointId &KpId,
                                                 const MatchedKeyPoints matches) {
        const auto &iterator = kp_matched_in_other_images.find(KpId);
        if (iterator == std::end(kp_matched_in_other_images)) {
            kp_matched_in_other_images.insert(std::make_pair(KpId, MatchedPointContainer{matches}));
        } else {
            kp_matched_in_other_images[KpId].emplace_back(matches);
        }
    }

} // namespace NSFeatureExtraction