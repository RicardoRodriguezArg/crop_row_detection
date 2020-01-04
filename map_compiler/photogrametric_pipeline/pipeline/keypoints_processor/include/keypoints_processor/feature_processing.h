#ifndef __PIPELINE_FEATURE_PROCESSING_H__
#define __PIPELINE_FEATURE_PROCESSING_H__

#include "feature_extraction_config.h"
#include "feature_extraction_task.h"
#include "interfaces/pipeline_process_interface.h"
namespace NSFeatureExtraction {
    class FeatureProcessing : public IPipelineProcess {
        public:
        FeatureProcessing(std::string &&directory_path, const int number_of_threads);
        ~FeatureProcessing();
        void setConfig(const NSConfig::FeatureExtracionConfig &config) noexcept;

        private:
        void execute() override;

        const int number_of_threads_;
        const std::string directory_path_;
        bool is_config_using_default_values = true;
        NSConfig::FeatureExtracionConfig config_;
        std::vector<FeatureExtractionTask> feature_container_ = {};
    };
} // namespace NSFeatureExtraction
#endif