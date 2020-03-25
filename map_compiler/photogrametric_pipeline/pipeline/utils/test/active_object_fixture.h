#ifndef __ACTIVE_OBJECT_FIXTURE_H__
#define __ACTIVE_OBJECT_FIXTURE_H__
#include "utils/active/active_object.h"
#include "utils/active/active_thread_pool.h"
#include <chrono>
#include <glog/logging.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
namespace {

    class ActiveMock : public NSActive::IActive {
        public:
        static int EXECUTE_TASK_DELAY_MS;
        explicit ActiveMock(const int id = 0) : callback_interface_(nullptr), task_id(id) {}
        void set_callback(const IActiveCallBackExecutorShared &callback_interface) override {
            callback_interface_ = callback_interface;
        }

        const IActiveCallBackExecutorShared &get_callback() const override {
            return callback_interface_;
        }

        void execute_task() override {
            std::chrono::milliseconds timespan(EXECUTE_TASK_DELAY_MS); // or whatever
            std::this_thread::sleep_for(timespan);
            task_executed_ = true;
            LOG(INFO) << "MOCK EXECUTING TASK : " << task_id;
            callback_interface_->update_state(NSActive::TaskState::EXECUTED_OK);
        }
        bool was_task_executed() const { return task_executed_; }
        void notify_with_callback() override { callback_interface_->notify(); }
        int get_task_id() const override { return task_id; }

        private:
        IActiveCallBackExecutorShared callback_interface_;
        bool task_executed_ = false;
        const int task_id = -1;
    };
    int ActiveMock::EXECUTE_TASK_DELAY_MS = 200;

    class ActiveCallBackMock : public NSActive::IActiveCallBackExecutor {
        public:
        static int NOTIFY_TIME_MS;
        void update_state(NSActive::TaskState state) override { current_state_ = state; }

        NSActive::TaskState get_state() const override { return current_state_; }

        void notify() override {
            std::chrono::milliseconds timespan(NOTIFY_TIME_MS); // or whatever
            std::this_thread::sleep_for(timespan);
        }

        private:
        NSActive::TaskState current_state_ = NSActive::TaskState::EXECUTED_FAIL;
    };
    int ActiveCallBackMock::NOTIFY_TIME_MS = 100;

    class ActiveObjectSetup : public ::testing::Test {
        protected:
        ~ActiveObjectSetup() override {}
        void SetUp() override {
            active_callback_mock = std::make_shared<ActiveCallBackMock>();
            active_mock = std::make_shared<ActiveMock>();
        }
        void setup_for_normal_scenario() {
            // setup mormal scenario for callback
            active_mock->set_callback(active_callback_mock);
        }
        void setup_for_scenario_nullptr_callback() {
            // setup mormal scenario for callback
            active_mock->set_callback(nullptr);
        }

        void setup_for_scenario_callback_TOO_SLOW_TASK_VERY_FAST() {
            // setup mormal scenario for callback
            ActiveMock::EXECUTE_TASK_DELAY_MS = 500;
            ActiveCallBackMock::NOTIFY_TIME_MS = 10;
            active_mock->set_callback(active_callback_mock);
        }

        void setup_for_scenario_callback_create_many_activities() {
            // setup mormal scenario for callback
            ActiveMock::EXECUTE_TASK_DELAY_MS = 50;
            ActiveCallBackMock::NOTIFY_TIME_MS = 10;
            active_mock->set_callback(active_callback_mock);
            for (int index = 0; index < callback_count; ++index) {
                active_mock_collection.emplace_back(std::make_shared<ActiveMock>(index));
                active_callback_mock_collection.emplace_back(
                    std::make_shared<ActiveCallBackMock>());
                active_mock_collection[index]->set_callback(active_callback_mock_collection[index]);
            }
        }

        void setup_for_scenario_callback_create_many_activities_with_empty_callback() {
            // setup mormal scenario for callback
            ActiveMock::EXECUTE_TASK_DELAY_MS = 50;
            ActiveCallBackMock::NOTIFY_TIME_MS = 10;
            active_mock->set_callback(active_callback_mock);
            for (int index = 0; index < callback_count; ++index) {
                active_mock_collection.emplace_back(std::make_shared<ActiveMock>());
                active_callback_mock_collection.emplace_back(
                    std::make_shared<ActiveCallBackMock>());
                active_mock_collection[index]->set_callback(nullptr);
            }
        }

        void wait(const int milliseconds) {
            std::chrono::milliseconds timespan(milliseconds); // or whatever
            std::this_thread::sleep_for(timespan);
        }
        std::shared_ptr<ActiveMock> active_mock = nullptr;
        std::shared_ptr<ActiveCallBackMock> active_callback_mock = nullptr;
        std::vector<std::shared_ptr<ActiveMock>> active_mock_collection;
        std::vector<std::shared_ptr<ActiveCallBackMock>> active_callback_mock_collection;
        const int callback_count = 15;
    };

} // namespace
#endif