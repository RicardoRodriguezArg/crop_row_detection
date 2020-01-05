#ifndef __PIPELINE_FEATURE_EXTRACTION_TASK_H__
#define __PIPELINE_FEATURE_EXTRACTION_TASK_H__

#include "feature_extraction.h"
#include <future>
#include <utils/cv_utils.h>
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
            return std::move(feature_extraction_ptr);
        }

        FEATURE_CONSTANTS::KEYPROCESS_INFO getTaskCurrentStatecurrent() const {
            return feature_extraction_ptr->currentState();
        }

        private:
        std::unique_ptr<FeatureExtraction> feature_extraction_ptr;
        const std::string filename_to_process_;
    };
} // namespace NSFeatureExtraction
#endif