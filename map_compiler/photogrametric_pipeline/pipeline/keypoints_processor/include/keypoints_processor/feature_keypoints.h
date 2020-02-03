#ifndef __PIPELINE_FEATURE_EXTRACTION_H__
#define __PIPELINE_FEATURE_EXTRACTION_H__
#include "feature_definitions.h"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <cstdint>
#include <glog/logging.h>
#include <memory>
#include <opencv2/opencv.hpp>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>
namespace NSFeatureExtraction {

    class FeatureExtraction {
        public:
        using FeatureExtractionPtr = std::unique_ptr<FeatureExtraction>;
        using KeyPointId = std::uint32_t;
        using ImageId = std::size_t;
        using GlobalKeyPointId = std::tuple<ImageId, KeyPointId>;
        using KeyPoints = std::vector<cv::KeyPoint>;
        using KeyPointDescriptor = cv::Mat;
        using MatchedKeyPoints = std::vector<cv::DMatch>;
        using MatchedPointContainer = std::vector<MatchedKeyPoints>;
        using ExternalKeyPointMap = std::unordered_map<KeyPointId, std::vector<MatchedKeyPoints>>;
        using KeyPointInfoUnit = std::tuple<KeyPointId, KeyPoints, KeyPointDescriptor>;

        constexpr static int KNN_BEST_MATCHED_VALUE{4};
        constexpr static float MATCH_RATIO_THRESHOLD{0.7f};
        explicit FeatureExtraction(const int max_features, const float match_percent_aceptable,
                                   const std::string &descriptor_name);

        void detectFeatures();
        // TODO: Remove this and apply Resource adquisition is Initialization idiom
        void setRawImage(const cv::Mat &raw_image);

        void match(const KeyPointInfoUnit &kp_unit);

        /*cv::Mat
        FindFundamentalMatrix(const std::vector<std::optional<cv::DMatch>> &matched_keypoints,
                              const std::vector<cv::KeyPoint> &other_descriptor) const;*/

        FEATURE_CONSTANTS::KEYPROCESS_INFO currentState() const;

        cv::Mat createPerpestiveMatrix(const std::vector<cv::DMatch> &matches,
                                       const std::vector<cv::KeyPoint> &keyPoints) const;

        const std::vector<cv::KeyPoint> getKeyPointContainer() const;
        std::vector<cv::KeyPoint> getKeyPoints() const;
        cv::Mat getKeyPointDescriptor() const;
        KeyPointInfoUnit getKeyPointInfoUnit() const;
        void setKeyPointId(const std::uint32_t &image_id) noexcept;
        cv::Mat getDescriptor() const;

        private:
        void checkPreliminars();
        void checkImageIsNotEmpty();
        void checkMatcherIsSet();

        void SetExternalKeyPoints(const KeyPointId &KpId, const MatchedKeyPoints matches);
        KeyPointId getId() const;
        std::vector<cv::DMatch>
        FilterMatches(const std::vector<std::vector<cv::DMatch>> &matched_keypoints) const;

        const int max_features_;
        const float match_percent_aceptable_;
        KeyPoints keyPoints_;
        cv::Mat descriptor_;
        // ORB Detector
        cv::Ptr<cv::Feature2D> orb_detector_;
        cv::Ptr<cv::DescriptorMatcher> matcher_;
        cv::Mat image_ = {};
        KeyPointId keypoint_id_ = {};
        ExternalKeyPointMap kp_matched_in_other_images;
        FEATURE_CONSTANTS::KEYPROCESS_INFO current_state_;
    };
} // namespace NSFeatureExtraction
#endif