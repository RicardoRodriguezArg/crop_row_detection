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

    std::vector<std::optional<cv::DMatch>>
    FeatureExtraction::match(const FeatureExtraction &other_feature_extraction) {
        return match(other_feature_extraction.getDescriptor(),
                     other_feature_extraction.getKeyPoints());
    }

    std::vector<std::optional<cv::DMatch>>
    FeatureExtraction::match(const cv::Mat &descriptor,
                             const std::vector<cv::KeyPoint> &keypoints) {
        std::vector<std::vector<cv::DMatch>> knn_matches{};
        std::vector<std::optional<cv::DMatch>> result{};
        matcher_->knnMatch(descriptor_, descriptor, knn_matches, KNN_BEST_MATCHED_VALUE);
        const auto filter_matches_index_mask = FilterMatches(knn_matches, keypoints);
        return result;
    }

    std::vector<cv::Mat>
    FeatureExtraction::FilterMatches(const std::vector<std::vector<cv::DMatch>> &matched_keypoints,
                                     const std::vector<cv::KeyPoint> &other_keypoint) const {
        std::vector<cv::Point2f> source;
        std::vector<cv::Point2f> target;
        std::vector<cv::Mat> mask;

        const auto &select_match_by_threshold = [this, &source, &target,
                                                 &other_keypoint](const auto &match) {
            if (match[0].distance < MATCH_RATIO_THRESHOLD * match[1].distance) {
                const auto query_index = match[0].queryIdx;
                const auto train_index = match[0].trainIdx;
                const auto &current_descriptor_index = keyPoints_[query_index].pt;
                const auto &other_descriptor_index = other_keypoint[train_index].pt;
                // source.emplace_back(std::make_tuple(query_index, current_descriptor_index));
                source.emplace_back(current_descriptor_index);
                // target.emplace_back(std::make_tuple(train_index, current_descriptor_index));
                target.emplace_back(current_descriptor_index);
            }
        };

        std::for_each(std::begin(matched_keypoints), std::end(matched_keypoints),
                      select_match_by_threshold);
        cv::findFundamentalMat(source, target, cv::FM_RANSAC, 3.0, 0.99, mask);
        return mask;
    }

    cv::Mat FeatureExtraction::FindFundamentalMatrix(
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

    FeatureExtraction::KeyPointId FeatureExtraction::getId() const { return keypoint_id_; }

    void FeatureExtraction::setKeyPointId(const std::uint32_t &image_id) noexcept {
        keypoint_id_ = image_id;
    }

    FEATURE_CONSTANTS::KEYPROCESS_INFO FeatureExtraction::currentState() const {
        return current_state_;
    }

    void FeatureExtraction::setExternalMatchedKeyPoints(
        const KeyPointId &id, const std::vector<std::optional<cv::DMatch>> &matches) {
        if (kp_matched_in_other_images.find(id) == std::end(kp_matched_in_other_images)) {
            kp_matched_in_other_images.insert(std::make_pair(id, matches));
        }
    }
} // namespace NSFeatureExtraction