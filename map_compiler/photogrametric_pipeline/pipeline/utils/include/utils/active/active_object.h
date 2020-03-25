#ifndef __ACTIVE_OBJECT_H__
#define __ACTIVE_OBJECT_H__

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <interfaces/active_callback_interface.h>
#include <iostream>
#include <thread>

namespace NSActive {

    class ActiveObject {
        public:
        ActiveObject() = default;

        void init() {
            if (thread_ == nullptr) {
                is_working_ = true;
                thread_.reset(new std::thread([this]() { run_async(); }));
            }
        }

        ~ActiveObject() { shutdown(); }

        bool is_working() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return is_working_;
        }

        bool is_data_ready() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return data_ready_;
        }

        void shutdown() {
            if (is_working_ && thread_ != nullptr) {
                {
                    const int max_retry = 3;
                    int current_attempt_retry{1};
                    while (data_ready_ && (current_attempt_retry < max_retry)) {
                        std::chrono::milliseconds timespan(10);
                        std::this_thread::sleep_for(timespan);
                        ++current_attempt_retry;
                    }

                    {
                        mutex_.lock();
                        is_working_ = false;
                        mutex_.unlock();
                    }
                    condition_variable_.notify_all();
                    thread_->join();
                }
            }
        }

        void execute_task_async(const std::shared_ptr<IActive> task) {

            if (is_working_ && (task != nullptr) && (data_ready_ == false)) {
                {

                    set_task_to_execute(task);

                    condition_variable_.notify_one();
                }
            }
        }

        bool is_free() const {
            std::lock_guard<std::mutex> lock{mutex_};
            const bool first = (data_ready_ == false);
            const bool result = (first && (is_working_ == true));
            return result;
        }

        private:
        void set_task_to_execute(const std::shared_ptr<IActive> task) {
            std::lock_guard<std::mutex> lock{mutex_};
            task_to_execute = task;
            data_ready_ = true;
        }

        void run_async() {

            while (is_working_) {
                std::unique_lock<std::mutex> unique_lock(mutex_);
                using namespace std::chrono_literals;
                condition_variable_.wait_for(unique_lock, 10ms, [this] {
                    return data_ready_ == true || is_working_ == true;
                });

                if (is_working_ && task_to_execute != nullptr) {

                    task_to_execute->execute_task();
                    if (task_to_execute->get_callback() != nullptr) {
                        task_to_execute->notify_with_callback();
                    }
                    task_to_execute = nullptr;
                    data_ready_ = false;
                }

                condition_variable_.notify_one();
                unique_lock.unlock();
                std::this_thread::yield();
            }
        }

        bool is_working_ = {false};
        bool data_ready_ = {false};
        std::shared_ptr<IActive> task_to_execute = nullptr;
        // const correctness for syncronized access
        // https://herbsutter.com/2013/05/24/gotw-6a-const-correctness-part-1-3/
        mutable std::mutex mutex_;
        std::condition_variable condition_variable_;
        std::unique_ptr<std::thread> thread_ = nullptr;
    };
} // namespace NSActive
#endif