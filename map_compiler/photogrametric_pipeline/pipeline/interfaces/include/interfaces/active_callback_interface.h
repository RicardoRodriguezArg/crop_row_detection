#ifndef __ACTIVE_CALLBACKS_INTERFACES_H__
#define __ACTIVE_CALLBACKS_INTERFACES_H__
namespace NSActive {

struct IActiveCallBack {
  virtual ~IActiveCallBack() = default;
  virtual void execute() = 0;
};

enum class TaskState { EXECUTED_FAIL, EXECUTED_OK };

struct IActive {
  virtual ~IActiveCallBack() = default;
  virtual TaskState execute_task() = 0;
};

struct IActiveCallBackExecutor {
  virtual ~IActiveCallBackExecutor() = default;
  virtual void update_state(TaskState) = 0;
};
}  // namespace NSActive
#endif