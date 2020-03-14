#ifndef __ACTIVE_THREAD_POOL_H__
#define __ACTIVE_THREAD_POOL_H__
#include <queue>
#include "active_object.h"

namespace NSActive {
class ThreadPool {
 public:
  explicit ThreadPool(
      const unsigned number_thread = std::thread::hardware_concurrency())
      : thread_pool{number_thread - 1U} {}

  ~ThreadPool() { stop_thread_pool(); }

  void stop_thread_pool() {
    if (thread_pool_is_running_.load()) {
      std::for_each(
          std::begin(thread_pool), std::end(thread_pool),
          [](const auto& active_worker) { active_worker.shutdown(); });

      thread_pool_is_running_ = false;
      thread_->join();
    }
  }

  void init() {
    if (thread_ == nullptr) {
      std::for_each(std::begin(thread_pool), std::end(thread_pool),
                    [](const auto& active_worker) { active_worker.init(); });
      thread_pool_is_running_ = true;
      thread_ = std::make_unique<std::thread>(&ThreadPool::process_tasks, this);
    }
  }
  void add_task_to_execute_async(const std::shared_ptr<IActiveCallBack> task) {
    if (thread_pool_is_running_ && task != nullptr) {
      add_task_to_queue(task);
      data_is_set_ = true;
      condition_variable_.notify_one();
    }
  }

 private:
  void add_task_to_queue(const std::shared_ptr<IActiveCallBack> task) {
    std::lock_guard<std::mutex> lock;
    task_queue.enque(task);
  }

  void process_tasks() {
    while (thread_pool_is_running_) {
      std::unique_lock<std::mutex> unique_lock(mutex);
      condition_variable_.wait(
          unique_lock, [] { return data_is_set_.load() || task_queue.empty() });
      data_is_set_ = false;
      if (!task_queue.empty()) {
        const auto task = task_queue.pop();
        const auto thread_for_work_iterator = std::find_if(
            std::begin(thread_pool), std::end(thread_pool),
            [](const auto active_worker) { return active_worker.is_free(); });
        if (thread_for_work_iterator != std::end(thread_pool)) {
          (*thread_for_work_iterator).execute_task_async(task);
        }
      }
    }
  }
  std::queue<std::shared_ptr<IActiveCallBack>> task_queue;
  const std::vector<ActiveObject> thread_pool;
  std::unique_ptr<std::thread> thread_ = nullptr;
  std::atomic<bool> data_is_set_ = false;
  std::atomic<bool> thread_pool_is_running_ = false;
  std::mutex mutex_;
  std::condition_variable condition_variable_;
};
}  // namespace NSActive

#endif