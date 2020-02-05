#ifndef __PIPELINE_FEATURE_EXTRACTION_TASK_H__
#define __PIPELINE_FEATURE_EXTRACTION_TASK_H__

#include "feature_keypoints.h"
#include <future>
#include <utils/cv_utils.h>
namespace NSFeatureExtraction {

    struct FeatureExtractionTask {

        template <typename Config>
        FeatureExtractionTask(Config config, const std::string &filename_to_process)
            : keypoint_processor_ptr(std::make_unique<FeatureExtraction>(
                  config.max_features_, config.match_percent_aceptable_, config.descriptor_name_)),
              filename_to_process_(filename_to_process) {}

        std::future<bool> run() {
            std::future<bool> result = std::async(
                std::launch::async,
                [ptr = std::move(keypoint_processor_ptr)](std::string filename_to_process_) {
                    const auto image =
                        NSFeatureExtraction::Utils::loadImageFromFileName(filename_to_process_);
                    bool result{false};
                    if (!image.empty()) {
                        ptr->setRawImage(image);
                        ptr->detectFeatures();
                        LOG(INFO) << "-->> SUCCESS PROCESSING IMAGE: " << filename_to_process_;
                        result = true;
                    }
                    LOG(INFO) << "Result of the operation: " << result;
                    return result;
                },
                filename_to_process_);
            return result;
        }

        std::unique_ptr<FeatureExtraction> getFeatureExtractionPtr() {
            return std::move(keypoint_processor_ptr);
        }

        FEATURE_CONSTANTS::KEYPROCESS_INFO getTaskCurrentStatecurrent() const {
            return keypoint_processor_ptr->currentState();
        }

        void matchKeyPoints(const FeatureExtraction::KeyPointInfoUnit &kp_info_unit) {

            keypoint_processor_ptr->match(kp_info_unit);
        }

        cv::Mat getKeyPointDescriptor() const {
            return keypoint_processor_ptr->getKeyPointDescriptor();
        }
        std::vector<cv::KeyPoint> getKeypoints() const {
            return keypoint_processor_ptr->getKeyPoints();
        }

        cv::Mat getKeyPointDescriptor() { return keypoint_processor_ptr->getKeyPointDescriptor(); }

        FeatureExtraction::KeyPointInfoUnit getKeyPointInfoUnit() const {
            return keypoint_processor_ptr->getKeyPointInfoUnit();
        }
        void setInitialsCameraMatrix(const cv::Mat &camera_matrix) {
            keypoint_processor_ptr->initializeTransformMatrix();
            keypoint_processor_ptr->initializeProyectionMatrix(camera_matrix);
        }

        private:
        std::unique_ptr<FeatureExtraction> keypoint_processor_ptr;
        const std::string filename_to_process_;
    };
} // namespace NSFeatureExtraction
#endif