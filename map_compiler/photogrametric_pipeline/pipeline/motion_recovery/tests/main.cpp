#include "keypoints_processor/feature_exceptions.h"
#include "keypoints_processor/feature_extraction_config.h"
#include "keypoints_processor/feature_extraction_task.h"
#include "keypoints_processor/feature_keypoints.h"

#include "utils/cv_utils.h"

#include "motion_recovery/motion_recovery.h"
#include <glog/logging.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Pipeline_Motion_Recovery {} // namespace Pipeline_Motion_Recovery

int main(int argc, char **argv) {
    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}