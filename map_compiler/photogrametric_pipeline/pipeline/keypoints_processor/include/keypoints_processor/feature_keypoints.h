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
        using KeyPoint = std::uint32_t;
        using ImageId = std::size_t;
        using KeyPointId = std::tuple<KeyPoint, ImageId>;
        constexpr static int KNN_BEST_MATCHED_VALUE{4};
        constexpr static float MATCH_RATIO_THRESHOLD{0.7f};
        explicit FeatureExtraction(const int max_features, const float match_percent_aceptable,
                                   const std::string &descriptor_name);

        void detectFeatures();
        // TODO: Remove this and apply Resource adquisition is Initialization idiom
        void setRawImage(const cv::Mat &raw_image);

        std::vector<std::optional<cv::DMatch>> match(const cv::Mat other_descriptor);

        cv::Mat
        FindFundamentalMatrix(const std::vector<std::optional<cv::DMatch>> &matched_keypoints,
                              const std::vector<cv::KeyPoint> &other_descriptor) const;

        FEATURE_CONSTANTS::KEYPROCESS_INFO currentState() const;

        cv::Mat createPerpestiveMatrix(const std::vector<cv::DMatch> &matches,
                                       const std::vector<cv::KeyPoint> &keyPoints) const;

        KeyPointId getKeyPointID() const;
        void setKeyPointId(const std::string &image_filename, const KeyPoint &local_keypoint);
        void addExternalReference(const KeyPointId external_keypoint_id);
        const std::vector<cv::KeyPoint> getKeyPointContainer() const;
        cv::Mat getKeyPointDescriptor() const;
        cv::Mat getKeyPointDescriptor();

        private:
        void checkPreliminars();
        void checkImageIsNotEmpty();
        void checkMatcherIsSet();
        const int max_features_;
        const float match_percent_aceptable_;
        std::vector<cv::KeyPoint> keyPoints_;
        cv::Mat descriptor_;
        // ORB Detector
        cv::Ptr<cv::Feature2D> orb_detector_;
        cv::Ptr<cv::DescriptorMatcher> matcher_;
        cv::Mat image_ = {};
        KeyPointId keypoint_id_ = {};
        // std::unordered_set<KeyPointId> matched_external_keypoints_;
        FEATURE_CONSTANTS::KEYPROCESS_INFO current_state_;
    };
} // namespace NSFeatureExtraction
#endif