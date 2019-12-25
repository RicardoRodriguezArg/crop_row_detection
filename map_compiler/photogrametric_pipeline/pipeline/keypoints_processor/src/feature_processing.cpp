#include "keypoints_processor/feature_processing.h"

#include <filesystem>
#include <string>
NSFeatureExtraction::FeatureProcessing::FeatureProcessing(std::string &&directory_path,
                                                          const int number_of_threads)
    : number_of_threads_(number_of_threads), directory_path_(std::move(directory_path))

{}

NSFeatureExtraction::FeatureProcessing::~FeatureProcessing() {}

void NSFeatureExtraction::FeatureProcessing::execute() {
    namespace fs = std::filesystem;
    int current_thread_index{0};
    std::vector<std::future<bool>> future_repo;
    future_repo.reserve(number_of_threads_);
    for (auto &entry : fs::directory_iterator(directory_path_)) {
        if (current_thread_index <= number_of_threads_) {
            ++current_thread_index;
            feature_container_.emplace_back(FeatureExtractionTask{config_});
            const auto path = entry.path();
            const std::string filename(path.filename().c_str());
            auto future = feature_container_.front().run(filename);
            // future_repo.emplace_back(future);
        } else {
            current_thread_index = 0;
            // wait for the result of the asyncs operations
            for (auto &future : future_repo) {
                future.get();
            }
        }
    }
    // 1.- Launch all image thread in paralell for keypoint and descripptor vector extraction
    // 2.- find matches in parallel, create map related of the keypoints and landmarks
    // 3.- Find fundamental/Perspective matrix
}

void NSFeatureExtraction::FeatureProcessing::setConfig(
    const NSConfig::FeatureExtracionConfig &config) {
    config_ = config;
}
