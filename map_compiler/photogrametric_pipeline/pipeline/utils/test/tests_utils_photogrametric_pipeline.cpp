
#include "active_object_fixture.h"
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

    TEST_F(ActiveObjectSetup, ACTIVE_OBJECT_TEST_HAPPY_PATH_EMPTY_ACTIVE_INTERFACE) {
        setup_for_normal_scenario();
        NSActive::ActiveObject active_object;
        active_object.init();
        EXPECT_EQ(true, active_object.is_free());
        active_object.execute_task_async(active_mock);
        EXPECT_EQ(false, active_object.is_free());

        EXPECT_NO_THROW(active_object.shutdown());
    }

    TEST_F(ActiveObjectSetup, ACTIVE_OBJECT_TEST_RUN_STESS_CYCLE_FOR_SANITY_CHECK) {
        setup_for_normal_scenario();
        NSActive::ActiveObject active_object;
        EXPECT_NO_THROW(active_object.init());
        EXPECT_EQ(true, active_object.is_free());
        EXPECT_NO_THROW(active_object.execute_task_async(active_mock));

        EXPECT_EQ(false, active_object.is_free());
        EXPECT_NO_THROW(active_object.shutdown());
    }

    TEST_F(ActiveObjectSetup, ACTIVE_OBJECT_TEST_CALLBACK_RUNNING_AT_100_MS_AND_TASK_AT_10_MS) {
        setup_for_scenario_callback_TOO_SLOW_TASK_VERY_FAST();
        NSActive::ActiveObject active_object;
        EXPECT_NO_THROW(active_object.init());
        EXPECT_EQ(true, active_object.is_free());
        EXPECT_NO_THROW(active_object.execute_task_async(active_mock));

        EXPECT_EQ(false, active_object.is_free());
        EXPECT_NO_THROW(active_object.shutdown());
    }

    TEST_F(ActiveObjectSetup, ACTIVE_OBJECT_TEST_MANY_ACTIVITIES) {
        ActiveCallBackMock::NOTIFY_TIME_MS = 5;
        ActiveCallBackMock::NOTIFY_TIME_MS = 10;
        setup_for_scenario_callback_create_many_activities();
        NSActive::ActiveObject active_object;
        EXPECT_NO_THROW(active_object.init());
        EXPECT_EQ(true, active_object.is_working());
        EXPECT_EQ(false, active_object.is_data_ready());
        EXPECT_EQ(true, active_object.is_free());
        EXPECT_EQ(false, active_object.is_data_ready());

        int index = 0;
        while (index < callback_count) {
            if (active_object.is_free()) {
                EXPECT_NO_THROW(active_object.execute_task_async(active_mock_collection[index]));
                ++index;
            } else {
                wait(1000);
            }
        }

        EXPECT_EQ(index, callback_count);
        EXPECT_EQ(true, active_object.is_free());
        EXPECT_NO_THROW(active_object.shutdown());
    }

    TEST_F(ActiveObjectSetup, ACTIVE_OBJECT_TEST_MANY_ACTIVITIES_WITH_EMPTY_CALLBACKS) {
        ActiveCallBackMock::NOTIFY_TIME_MS = 5;
        ActiveCallBackMock::NOTIFY_TIME_MS = 100;
        setup_for_scenario_callback_create_many_activities_with_empty_callback();
        NSActive::ActiveObject active_object;
        EXPECT_NO_THROW(active_object.init());
        EXPECT_EQ(true, active_object.is_working());
        EXPECT_EQ(false, active_object.is_data_ready());
        EXPECT_EQ(true, active_object.is_free());
        EXPECT_EQ(false, active_object.is_data_ready());

        int index = 0;
        while (index < callback_count) {
            if (active_object.is_free()) {
                EXPECT_NO_THROW(active_object.execute_task_async(active_mock_collection[index]));
                ++index;
            } else {
                wait(1000);
            }
        }

        EXPECT_EQ(index, callback_count);
        EXPECT_EQ(true, active_object.is_free());
        EXPECT_NO_THROW(active_object.shutdown());
    }

} // namespace
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    FLAGS_logtostderr = true;
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}