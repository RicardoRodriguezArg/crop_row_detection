#include "keypoints_processor/feature_processing.h"
#include <algorithm>
#include <filesystem>
#include <glog/logging.h>
#include <string>
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
    for (const auto &feature_process : feature_container_) {
        auto future = feature_container_.front().run();
        if (current_thread_index < number_of_threads_) {
            future_repo.emplace_back(std::move(future));
        } else {
            for (auto &future : future_repo) {
                future.get();
                LOG(INFO) << "Async done job!: " << current_thread_index;
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
    LOG(INFO) << "Extraction filenames to process ";
    namespace fs = std::filesystem;
    for (auto &entry : fs::directory_iterator(directory_path_)) {

        const auto path = entry.path();
        const std::string filename(path.filename().c_str());
        LOG(INFO) << "Image to Process: " << filename;
        feature_container_.emplace_back(FeatureExtractionTask{config_, filename});
        files_to_process.emplace_back(filename);
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
