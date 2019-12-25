#ifndef __PIPELINE_INTERFACES_H__
#define __PIPELINE_INTERFACES_H__
namespace NSFeatureExtraction {
    struct IPipelineProcess {
        virtual ~IPipelineProcess() = default;
        virtual void execute() = 0;
    };
} // namespace NSFeatureExtraction
#endif