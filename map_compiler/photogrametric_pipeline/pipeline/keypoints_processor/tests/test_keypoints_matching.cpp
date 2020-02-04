#include "keypoints_processor/feature_exceptions.h"
#include "keypoints_processor/feature_extraction_config.h"
#include "keypoints_processor/feature_extraction_task.h"
#include "keypoints_processor/feature_keypoints.h"

#include "utils/cv_utils.h"
//#include "keypoints_processor/keypoints_repository.h"
#include <glog/logging.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <gtest/gtest.h>
namespace Pipeline_keypoints_matching {} // namespace Pipeline_keypoints_matching
int main(int argc, char **argv) {
    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}