#ifndef __PIPELINE_INTERFACES_H__
#define __PIPELINE_INTERFACES_H__
namespace NSFeatureExtraction {
    struct IPipelineProcess {
        virtual ~IPipelineProcess() = default;
        virtual void extractKeypointFeature() = 0;
        virtual void FoundMatchedKeyPoints() = 0;
        virtual void computeMotionRecovery() = 0;
    };
} // namespace NSFeatureExtraction
#endif