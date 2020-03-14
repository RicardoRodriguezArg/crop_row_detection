#ifndef __ACTIVE_OBJECT_H__
#define __ACTIVE_OBJECT_H__

#include <atomic>
#include <condition_variable>
#include <thread>
#include "active_callbacks.h"
namespace NSActive {

class ActiveObject {
 public:
  ActiveObject() = default;

  void init() {
    if (thread_ == nullptr) {
      is_working_ = true;
      thread_ = std::make_unique<std::thread>(&ActiveObject::run_async);
    }
  }

  ~ActiveObject() { shutdown(); }

  void shutdown() {
    if (is_working_) {
      is_working_ = false;
      thread_->join();
    }
  }

  void execute_task_async(const std::shared_ptr<IActiveCallBack> task) {
    if (is_working_) {
      set_task_to_execute(task);
      condition_variable_.notify_one();
    }
  }

  bool is_free() const { return !data_ready_.load(); }

 private:
  void set_task_to_execute(const TaskType task) {
    std::lock_guard<std::mutex> lock_guard(mutex_);
    tak_to_execute = task;
    data_ready_ = true;
  }

  void run_async() {
    while (is_working_) {
      std::unique_lock<std::mutex> unique_lock(mutex_);
      condition_variable_.wait(unique_lock, [] { return data_ready_.load(); });
      tak_to_execute->execute();
      data_ready_ = false;
    }
  }

  std::atomic<bool> is_working_ = {false};
  std::atomic<bool> data_ready_ = {false};
  std::shared_ptr<IActiveCallBack> tak_to_execute = nullptr;
  std::mutex mutex_;
  std::condition_variable condition_variable_;
  std::unique_ptr<std::thread> thread_ = nullptr;
};
}  // namespace NSActive
#endif