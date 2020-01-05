#ifndef __PIPELINE_FEATURE_EXTRACTION_TASK_H__
#define __PIPELINE_FEATURE_EXTRACTION_TASK_H__

#include "feature_extraction.h"
#include <future>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

namespace NSFeatureExtraction {

    struct FeatureExtractionTask {
        template <typename Config>
        FeatureExtractionTask(Config config, const std::string &filename_to_process)
            : feature_extraction_ptr(std::make_unique<FeatureExtraction>(
                  config.max_features_, config.match_percent_aceptable_, config.descriptor_name_)),
              filename_to_process_(filename_to_process) {}

        std::future<bool> run() {
            std::future<bool> result = std::async(
                std::launch::async,
                [ptr = std::move(feature_extraction_ptr)](std::string filename_to_process_) {
                    cv::Mat image_raw = cv::imread(filename_to_process_, cv::IMREAD_GRAYSCALE);
                    bool result{false};
                    if (image_raw.data) {
                        ptr->setRawImage(image_raw);
                        ptr->detectFeatures();
                        result = true;
                    }
                    return result;
                },
                filename_to_process_);
            return result;
        }

        std::unique_ptr<FeatureExtraction> getFeatureExtractionPtr() {
            return std::move(feature_extraction_ptr);
        }

        private:
        std::unique_ptr<FeatureExtraction> feature_extraction_ptr;
        const std::string filename_to_process_;
    };
} // namespace NSFeatureExtraction
#endif