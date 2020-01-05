#include "keypoints_processor/feature_processing.h"
#include <algorithm>
#include <filesystem>
#include <glog/logging.h>

NSFeatureExtraction::FeatureProcessing::FeatureProcessing(std::string &&directory_path,
                                                          const int number_of_threads)
    : number_of_threads_(number_of_threads), directory_path_(std::move(directory_path))

{}

NSFeatureExtraction::FeatureProcessing::~FeatureProcessing() {}

void NSFeatureExtraction::FeatureProcessing::execute() {
    if (is_config_using_default_values) {
        LOG(INFO) << "Using Default Values, config was not setup";
    }
    extractFilenamesToProcess();
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
                LOG(INFO) << "Async done job!: " << current_thread_index;
                LOG(INFO) << "Result of the Thread: " << result;
            }
            future_repo.clear();
            current_thread_index = 0;
        }
    }
    // 1.- Launch all image thread in paralell for keypoint and descripptors
    // vectors extraction 2.- find matches in parallel, create map related of the
    // keypoints and landmarks 3.- Find fundamental/Perspective matrix
}

void NSFeatureExtraction::FeatureProcessing::extractFilenamesToProcess() {
    namespace fs = std::filesystem;
    for (auto &entry : fs::directory_iterator(directory_path_)) {
        if (entry.is_regular_file()) {
            feature_container_.emplace_back(FeatureExtractionTask{config_, entry.path()});
            files_to_process.emplace_back(entry.path());
        }
    }
    std::sort(std::begin(files_to_process), std::end(files_to_process));
}

void NSFeatureExtraction::FeatureProcessing::setConfig(
    const NSConfig::FeatureExtracionConfig &config) noexcept {
    config_ = config;
}

NSFeatureExtraction::FeatureProcessing::FeatureExtractionContainer &
NSFeatureExtraction::FeatureProcessing::getFeatureExtractionContainer() {
    return feature_container_;
}
std::size_t NSFeatureExtraction::FeatureProcessing::getImagesProcessingCount() {
    return files_to_process.size();
}
