
#include "factory/generic_factory.h"
#include <gtest/gtest.h>
namespace {
    TEST(GENERIC_FACTORY_TESTS, Creation_HAPPY_PATH_REGISTRATION) {
        auto &factory = NSPipelineUtils::Factory::getInstance();
        EXPECT_EQ(true, factory.isEmpty());
        NSPipelineUtils::Factory::releaseSingleton();
    }
} // namespace
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}