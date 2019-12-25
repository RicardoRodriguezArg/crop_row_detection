#include "keypoints_processor/feature_extraction.h"
#include "keypoints_processor/feature_extraction_config.h"
#include "keypoints_processor/feature_extraction_task.h"
#include "keypoints_processor/feature_processing.h"
//#include "keypoints_processor/keypoints_repository.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Pipeline_keypoints_processor {
    TEST(KEYPOINT_PROCESSOR, KEYPOINT_PROCESSOR_ok) {}
} // namespace Pipeline_keypoints_processor

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}