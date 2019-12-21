#pragma once
#include "../../interfaces/src/pipeline_process_interface.h"
#include "feature_extraction_config.h"
#include "feature_extraction_task.h"
namespace NSFeatureExtraction {
    class FeatureProcessing : public IPipelineProcess {
        public:
        FeatureProcessing(std::string &&directory_path, const int number_of_threads);
        ~FeatureProcessing();
        void setConfig(const NSConfig::FeatureExtracionConfig &config);

        private:
        void execute() override;
        const int number_of_threads_;
        const std::string directory_path_;
        NSConfig::FeatureExtracionConfig config_;
        std::vector<FeatureExtractionTask> feature_container_ = {};
    };
} // namespace NSFeatureExtraction