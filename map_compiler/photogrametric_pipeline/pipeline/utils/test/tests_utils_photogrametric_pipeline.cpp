
#include "utils/active/active_callbacks.h"
#include "utils/cv_utils.h"
#include "utils/factory_base.h"
#include "utils/generic_factory.h"

#include <gtest/gtest.h>
namespace {
    class GenericClassToRegisterInFactory : public NSPipelineUtils::FactoryBase {
        private:
        virtual int getID() { return 2; }
    };

    TEST(GENERIC_FACTORY_TESTS, Creation_HAPPY_PATH_INSTATIATION) {
        auto &factory = NSPipelineUtils::Factory::getInstance();
        EXPECT_EQ(true, factory.isEmpty());
        NSPipelineUtils::Factory::releaseSingleton();
    }

    TEST(GENERIC_FACTORY_TESTS, Creation_REGISTRATION_PATH) {
        auto &factory = NSPipelineUtils::Factory::getInstance();
        EXPECT_EQ(true, factory.isEmpty());
        auto register_function = [](void) -> std::unique_ptr<NSPipelineUtils::FactoryBase> {
            auto ptr = std::make_unique<GenericClassToRegisterInFactory>();
            return ptr;
        };
        factory.registerFactoryFunction("GenericClassToRegisterInFactory", register_function);
        EXPECT_EQ(1u, factory.getInstancesCount());
        auto instance_in_factory = factory.getInstancePtr("GenericClassToRegisterInFactory");
        EXPECT_EQ(2, instance_in_factory->getID());
        factory.releaseResources();
        EXPECT_EQ(true, factory.isEmpty());
        NSPipelineUtils::Factory::releaseSingleton();
    }

    TEST(GENERIC_FACTORY_TESTS, Creation_REGISTRATION_AND_INSTANCE_PATH) {
        auto &factory = NSPipelineUtils::Factory::getInstance();
        EXPECT_EQ(true, factory.isEmpty());
        auto register_function = [](void) -> std::unique_ptr<NSPipelineUtils::FactoryBase> {
            auto ptr = std::make_unique<GenericClassToRegisterInFactory>();
            return ptr;
        };
        factory.registerFactoryFunction("GenericClassToRegisterInFactory", register_function);
        EXPECT_EQ(1u, factory.getInstancesCount());
        auto instance_in_factory = factory.getInstancePtr("GenericClassToRegisterInFactory");
        EXPECT_EQ(2, instance_in_factory->getID());
        factory.releaseResources();
        EXPECT_EQ(true, factory.isEmpty());
        NSPipelineUtils::Factory::releaseSingleton();
    }

    TEST(GENERIC_FACTORY_TESTS, Creation_REGISTRATION_PATH_FAIL) {
        auto &factory = NSPipelineUtils::Factory::getInstance();
        EXPECT_EQ(true, factory.isEmpty());
        auto register_function = [](void) -> std::unique_ptr<NSPipelineUtils::FactoryBase> {
            auto ptr = std::make_unique<GenericClassToRegisterInFactory>();
            return ptr;
        };
        factory.registerFactoryFunction("GenericClassToRegisterInFactory", register_function);
        EXPECT_EQ(1u, factory.getInstancesCount());
        auto instance_in_factory = factory.getInstancePtr("GenericClassToRegisterInFactorx");
        EXPECT_EQ(nullptr, instance_in_factory);
        factory.releaseResources();
        EXPECT_EQ(true, factory.isEmpty());
        NSPipelineUtils::Factory::releaseSingleton();
    }

    TEST(CV_UTILS_TESTS, LOAD_IMAGE_OK) {
        const auto filename{"resources/image_a.png"};
        const auto image = NSFeatureExtraction::Utils::loadImageFromFileName(filename);
        EXPECT_EQ(false, image.empty());
    }

    TEST(CV_UTILS_TESTS, LOAD_IMAGE_FAIL) {
        const auto filename{"resources/image_.png"};
        const auto image = NSFeatureExtraction::Utils::loadImageFromFileName(filename);
        EXPECT_EQ(true, image.empty());
    }

    TEST(CV_UTILS_TESTS, CONVERT_IMAGE_TO_GREY_SCALE_OK) {
        const auto filename{"resources/image_a.png"};
        const auto image = NSFeatureExtraction::Utils::loadImageFromFileName(filename);
        EXPECT_EQ(false, image.empty());
        const auto grey_image = NSFeatureExtraction::Utils::convertToGreyScale(image);
        EXPECT_EQ(false, grey_image.empty());
    }
} // namespace
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}