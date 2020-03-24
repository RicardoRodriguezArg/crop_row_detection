#include "keypoints_processor/feature_exceptions.h"
#include "keypoints_processor/feature_extraction_config.h"
#include "keypoints_processor/feature_extraction_task.h"
#include "keypoints_processor/feature_keypoints.h"

#include "utils/cv_utils.h"

#include "processor/pipeline_processor.h"
#include <glog/logging.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace NSOrtho_Processing {
    TEST(ORTHO_PROCESSING_TASK_MULTITHREAD_APPROACH, EXTRACT_FEATURE_MULTIPLE_IMAGES_OK) {
        // parameters for Multithread processing
        const int max_thread_count{4};
        NSFeatureExtraction::MultiThreadFeatureProcessing feature_processing{"./resources",
                                                                             max_thread_count};
        feature_processing.extractKeypointFeature();
        ASSERT_EQ(feature_processing.getImagesProcessingCount(),
                  feature_processing.getFeatureExtractionContainer().size());
        // load image mat from file
    }

    TEST(ORTHO_PROCESSING_TASK_MULTITHREAD_APPROACH,
         EXTRACT_FEATURE_MULTIPLE_IMAGES_PARAMETER_CHECK_TUNNING_OK) {
        // parameters for Multithread processing
        const int max_thread_count{10};
        NSFeatureExtraction::MultiThreadFeatureProcessing feature_processing{"./resources",
                                                                             max_thread_count};
        feature_processing.extractKeypointFeature();
        ASSERT_EQ(feature_processing.getImagesProcessingCount(),
                  feature_processing.getFeatureExtractionContainer().size());
    }
    /*
    TEST(ORTHO_PROCESSING_TASK, SIMPLE_MATCHING) {
        // parameters for Multithread processing
        const int max_thread_count{10};
        NSFeatureExtraction::MultiThreadFeatureProcessing feature_processing{
            "./resources/keypoint_matching", max_thread_count};
        feature_processing.extractKeypointFeature();

        feature_processing.FoundMatchedKeyPoints();
    }*/
} // namespace NSOrtho_Processing

int main(int argc, char **argv) {
    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}