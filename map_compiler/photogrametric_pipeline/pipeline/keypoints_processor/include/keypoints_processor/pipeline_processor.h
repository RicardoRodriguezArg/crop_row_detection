#ifndef __PIPELINE_PROCESSOR_PROCESSING_H__
#define __PIPELINE_PROCESSOR_PROCESSING_H__

#include "feature_definitions.h"
#include "feature_extraction_config.h"
#include "feature_extraction_task.h"
#include "interfaces/pipeline_process_interface.h"
namespace NSFeatureExtraction {
    class MultiThreadFeatureProcessing : public IPipelineProcess {

        public:
        using KeyPointsFeaturesContainer = std::vector<FeatureExtractionTask>;
        using FeatureExtractionInfo = std::vector<std::string>;
        MultiThreadFeatureProcessing(std::string &&directory_path, const int number_of_threads);

        void setConfig(const NSConfig::FeatureExtracionConfig &config) noexcept;
        KeyPointsFeaturesContainer &getFeatureExtractionContainer();
        std::size_t getImagesProcessingCount();
        void extractKeypointFeature() override;
        void FoundMatchedKeyPoints() override;
        void setupInitialMatrix() const;

        private:
        bool isValidKeyPoint(const FeatureExtractionTask &feature_task) const;
        void extractFilenamesToProcess();
        const int number_of_threads_;
        const std::string directory_path_;
        bool is_config_using_default_values = true;
        NSConfig::FeatureExtracionConfig config_;
        KeyPointsFeaturesContainer feature_container_ = {};
        FeatureExtractionInfo files_to_process = {};
    };
} // namespace NSFeatureExtraction
#endif