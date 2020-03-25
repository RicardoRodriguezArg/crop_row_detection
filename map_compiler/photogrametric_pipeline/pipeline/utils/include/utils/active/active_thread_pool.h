#ifndef __ACTIVE_THREAD_POOL_H__
#define __ACTIVE_THREAD_POOL_H__
#include "active_object.h"
#include <algorithm>
#include <glog/logging.h>
#include <queue>

namespace NSActive {
    class ThreadPool {
        public:
        explicit ThreadPool(const unsigned number_thread = std::thread::hardware_concurrency())
            : thread_pool{number_thread - 1U} {}

        ~ThreadPool() { stop_thread_pool(); }

        void stop_thread_pool() {
            if (thread_pool_is_running_) {
                std::for_each(std::begin(thread_pool), std::end(thread_pool),
                              [](auto &active_worker) { active_worker.shutdown(); });

                const int max_retry = 3;
                int current_attempt_retry{1};
                while (!task_queue.empty() && current_attempt_retry < max_retry) {
                    LOG(INFO) << "Waitting for queue to complete task for shutdown";
                    std::chrono::milliseconds timespan(10);
                    std::this_thread::sleep_for(timespan);
                    ++current_attempt_retry;
                }
                {
                    std::lock_guard<std::mutex> lock(mutex_);
                    thread_pool_is_running_ = false;
                }
                condition_variable_.notify_one();
                thread_->join();
            }
        }

        void init() {
            if (thread_ == nullptr) {
                std::for_each(std::begin(thread_pool), std::end(thread_pool),
                              [](auto &active_worker) { active_worker.init(); });
                thread_pool_is_running_ = true;
                thread_.reset(new std::thread([this]() { run_pool(); }));
            }
        }

        void add_task_to_execute_async(const std::shared_ptr<IActive> task) {
            if (thread_pool_is_running_ && task != nullptr) {
                add_task_to_queue(task);

                condition_variable_.notify_one();
            }
        }

        private:
        void add_task_to_queue(const std::shared_ptr<IActive> task) {
            std::lock_guard<std::mutex> lock(mutex_);
            task_queue.push(task);
        }

        void run_pool() {
            while (thread_pool_is_running_) {
                std::unique_lock<std::mutex> unique_lock(mutex_);
                using namespace std::chrono_literals;
                condition_variable_.wait_for(unique_lock, 10ms,
                                             [this] { return !task_queue.empty(); });

                if (!task_queue.empty() && thread_pool_is_running_) {
                    const auto task = task_queue.front();
                    task_queue.pop();
                    const auto thread_for_work_iterator = std::find_if(
                        std::begin(thread_pool), std::end(thread_pool),
                        [](const auto &active_worker) { return active_worker.is_free(); });
                    if (thread_for_work_iterator != std::end(thread_pool)) {
                        (*thread_for_work_iterator).execute_task_async(task);
                    } else {
                        LOG(INFO)
                            << "Thread pool bussy, cannot find any thread free for process request";
                    }
                }
                condition_variable_.notify_one();
                unique_lock.unlock();
            }
        }

        std::queue<std::shared_ptr<IActive>> task_queue;
        std::vector<ActiveObject> thread_pool;
        std::unique_ptr<std::thread> thread_ = nullptr;
        bool thread_pool_is_running_ = false;
        std::mutex mutex_;
        std::condition_variable condition_variable_;
    };
} // namespace NSActive

#endif