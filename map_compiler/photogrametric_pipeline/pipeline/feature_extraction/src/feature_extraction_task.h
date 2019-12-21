#pragma once

#include "feature_extraction.h"
#include <future>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

namespace NSFeatureExtraction {

    struct FeatureExtractionTask {
        template <typename Config>
        FeatureExtractionTask(Config config)
            : feature_extraction_ptr(std::make_unique<FeatureExtraction>(
                  config.max_features_, config.match_percent_aceptable_, config.descriptor_name_)) {
        }

        std::future<bool> run(std::string path_to_image) {
            std::future<bool> result = std::async(
                std::launch::async,
                [ptr = std::move(feature_extraction_ptr)](std::string file_to_load) {
                    cv::Mat image_raw = cv::imread(file_to_load, cv::IMREAD_GRAYSCALE);
                    bool result{false};
                    if (image_raw.data) {
                        ptr->setRawImage(image_raw);
                        ptr->detectFeatures();
                        result = true;
                    }
                    return result;
                },
                path_to_image);
            return result;
        }

        std::unique_ptr<FeatureExtraction> getFeatureExtractionPtr() {
            return std::move(feature_extraction_ptr);
        }

        private:
        std::unique_ptr<FeatureExtraction> feature_extraction_ptr;
    };
} // namespace NSFeatureExtraction