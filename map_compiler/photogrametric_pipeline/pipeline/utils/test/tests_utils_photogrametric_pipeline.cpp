
#include "factory/factory_base.h"
#include "factory/generic_factory.h"

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
} // namespace
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}