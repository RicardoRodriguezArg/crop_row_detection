#include "keypoints_processor/feature_extraction.h"
#include "keypoints_processor/feature_extraction_config.h"
#include "keypoints_processor/feature_extraction_task.h"
#include "keypoints_processor/feature_processing.h"
//#include "keypoints_processor/keypoints_repository.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Pipeline_keypoints_processor {
    TEST(KEYPOINT_EXTRACTION_CLASSIC_APPROACH, KEYPOINT_PROCESSOR_ok) {
        constexpr int max_features{};
        const float match_percent_aceptable{};
        const std::string &descriptor_name{""};
        const NSFeatureExtraction::FeatureExtraction feature_extraction{
            max_features, match_percent_aceptable, descriptor_name};
    }
} // namespace Pipeline_keypoints_processor

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}