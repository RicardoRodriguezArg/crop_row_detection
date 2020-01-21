#include "keypoints_processor/feature_processing_task_based.h"
#include <algorithm>
#include <filesystem>
#include <glog/logging.h>

NSFeatureExtraction::MultiThreadFeatureProcessing::MultiThreadFeatureProcessing(
    std::string &&directory_path, const int number_of_threads)
    : number_of_threads_(number_of_threads), directory_path_(std::move(directory_path))

{}

void NSFeatureExtraction::MultiThreadFeatureProcessing::extractKeypointFeature() {
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
    // 1.- Launch all image thread in paralell for keypoint and descripptors
    // vectors extraction 2.- find matches in parallel, create map related of the
    // keypoints and landmarks 3.- Find fundamental/Perspective matrix
}

bool NSFeatureExtraction::MultiThreadFeatureProcessing::isValidKeyPoint(
    const FeatureExtractionTask &feature_task) const {
    return feature_task.getTaskCurrentStatecurrent() == FEATURE_CONSTANTS::KEYPROCESS_INFO::OK;
}

void NSFeatureExtraction::MultiThreadFeatureProcessing::FoundMatchedKeyPoints() {

    const auto end_iterator = std::end(feature_container_);
    for (auto iterator = std::begin(feature_container_); iterator != end_iterator; ++iterator) {
        auto &current_keypoint = *iterator;
        if (isValidKeyPoint(current_keypoint)) {
            auto keypoint_comparator = [&, iterator](const FeatureExtractionTask &next_keypoint) {
                if (isValidKeyPoint(next_keypoint)) {
                    const auto next_keypoint_descriptor = next_keypoint.getKeyPointDescriptor();
                    // TODO: Fix Input for macthed keypoints
                    /*const auto match_keypoints =
                        current_keypoint.matchKeyPoints(next_keypoint_descriptor);*/
                }
            };

            std::for_each(std::next(iterator), end_iterator, keypoint_comparator);
        }
    }
}

void NSFeatureExtraction::MultiThreadFeatureProcessing::extractFilenamesToProcess() {
    namespace fs = std::filesystem;
    for (auto &entry : fs::directory_iterator(directory_path_)) {
        if (entry.is_regular_file()) {
            feature_container_.emplace_back(FeatureExtractionTask{config_, entry.path()});
            files_to_process.emplace_back(entry.path());
        }
    }
    std::sort(std::begin(files_to_process), std::end(files_to_process));
}

void NSFeatureExtraction::MultiThreadFeatureProcessing::setConfig(
    const NSConfig::FeatureExtracionConfig &config) noexcept {
    config_ = config;
}

NSFeatureExtraction::MultiThreadFeatureProcessing::KeyPointsFeaturesContainer &
NSFeatureExtraction::MultiThreadFeatureProcessing::getFeatureExtractionContainer() {
    return feature_container_;
}
std::size_t NSFeatureExtraction::MultiThreadFeatureProcessing::getImagesProcessingCount() {
    return files_to_process.size();
}
