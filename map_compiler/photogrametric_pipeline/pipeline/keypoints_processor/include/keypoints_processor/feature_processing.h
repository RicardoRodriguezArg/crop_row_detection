#ifndef __PIPELINE_FEATURE_PROCESSING_H__
#define __PIPELINE_FEATURE_PROCESSING_H__

#include "feature_extraction_config.h"
#include "feature_extraction_task.h"
#include "interfaces/pipeline_process_interface.h"

namespace NSFeatureExtraction {
    class FeatureProcessing : public IPipelineProcess {
        public:
        using FeatureExtractionContainer = std::vector<FeatureExtractionTask>;
        FeatureProcessing(std::string &&directory_path, const int number_of_threads);
        ~FeatureProcessing();
        void setConfig(const NSConfig::FeatureExtracionConfig &config) noexcept;
        std::vector<FeatureExtractionTask> &getFeatureExtractionContainer();
        std::size_t getImagesProcessingCount();
        void execute() override;
        std::optional<int> computeImageCountToProcess();

        private:
        void extractFilenamesToProcess();
        const int number_of_threads_;
        const std::string directory_path_;
        bool is_config_using_default_values = true;
        NSConfig::FeatureExtracionConfig config_;
        FeatureExtractionContainer feature_container_ = {};
        std::vector<std::string> files_to_process = {};
    };
} // namespace NSFeatureExtraction
#endif