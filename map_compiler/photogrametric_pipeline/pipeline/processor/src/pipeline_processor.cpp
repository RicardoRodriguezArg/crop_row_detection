#include "processor/pipeline_processor.h"
#include <algorithm>
#include <filesystem>
#include <glog/logging.h>
namespace NSFeatureExtraction {
    MultiThreadFeatureProcessing::MultiThreadFeatureProcessing(std::string &&directory_path,
                                                               const int number_of_threads)
        : number_of_threads_(number_of_threads), directory_path_(std::move(directory_path))

    {}

    void MultiThreadFeatureProcessing::setupInitialMatrix() const {}
    void MultiThreadFeatureProcessing::extractKeypointFeature() {
        if (is_config_using_default_values) {
            LOG(INFO) << "Using Default Values, config was not setup";
        }
        extractFilenamesToProcess();
        // TODO: REFACTOR
        int current_thread_index{0};
        std::vector<std::future<bool>> future_repo;
        future_repo.reserve(files_to_process.size());
        for (auto &feature_process : feature_container_) {
            auto future = feature_process.run();
            if (current_thread_index < number_of_threads_) {
                future_repo.emplace_back(std::move(future));
                ++current_thread_index;
            } else {
                for (auto &future : future_repo) {
                    const bool result = future.get();
                }
                future_repo.clear();
                current_thread_index = 0;
            }
        }
    }

    bool
    MultiThreadFeatureProcessing::isValidKeyPoint(const FeatureExtractionTask &feature_task) const {
        return feature_task.getTaskCurrentStatecurrent() == FEATURE_CONSTANTS::KEYPROCESS_INFO::OK;
    }

    void MultiThreadFeatureProcessing::FoundMatchedKeyPoints() {
        LOG(INFO) << "Matching extracted keypoints";
        const auto end_iterator = std::end(feature_container_);
        for (auto iterator = std::begin(feature_container_); iterator != end_iterator; ++iterator) {
            auto &current_keypoint = *iterator;
            if (isValidKeyPoint(current_keypoint)) {
                LOG(INFO) << "Validating current_keypoint";
                auto keypoint_lamda_matcher =
                    [&, iterator](const FeatureExtractionTask &next_keypoint) {
                        LOG(INFO) << "Validating Next_keypoint";
                        if (isValidKeyPoint(next_keypoint)) {
                            LOG(INFO) << "Matching KeyPoints";
                            current_keypoint.matchKeyPoints(next_keypoint.getKeyPointInfoUnit());
                        }
                    };

                std::for_each(iterator + 1, end_iterator, keypoint_lamda_matcher);
            }
        }
    }

    void MultiThreadFeatureProcessing::setupInitialImagePoseMatrix() {
        // TODO: create method to check image size on all input set
        if (!files_to_process.empty()) {
            const auto &image_size = Utils::getImageDimension(files_to_process.front());
            const auto &cameraMatrix =
                NSFeatureExtraction::FeatureExtraction::createCameraMatrix(image_size);
            feature_container_.at(0).setInitialsCameraMatrix(cameraMatrix);
        }
    }

    void MultiThreadFeatureProcessing::computeMotionRecovery() {
        setupInitialImagePoseMatrix();
        const auto functor = [](const auto &current, const auto &next) {
            current.findEssentialMatrix(next.getKeyPointInfoUnit());
            const auto &next_source_points = next.getSourcePointPosition();
            current.recoverPose(next_source_points);
            // should check is not empty
        };
        Generics::iterate_over_all_in_pairs(std::begin(feature_container_),
                                            std::end(feature_container_), functor);
    }

    void MultiThreadFeatureProcessing::extractFilenamesToProcess() {
        namespace fs = std::filesystem;
        for (auto &entry : fs::directory_iterator(directory_path_)) {
            if (entry.is_regular_file()) {
                feature_container_.emplace_back(FeatureExtractionTask{config_, entry.path()});
                files_to_process.emplace_back(entry.path());
            }
        }
        std::sort(std::begin(files_to_process), std::end(files_to_process));
    }

    void MultiThreadFeatureProcessing::setConfig(
        const NSConfig::FeatureExtracionConfig &config) noexcept {
        config_ = config;
    }

    MultiThreadFeatureProcessing::KeyPointsFeaturesContainer &
    MultiThreadFeatureProcessing::getFeatureExtractionContainer() {
        return feature_container_;
    }
    std::size_t MultiThreadFeatureProcessing::getImagesProcessingCount() {
        return files_to_process.size();
    }
} // namespace NSFeatureExtraction