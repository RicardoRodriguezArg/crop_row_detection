#ifndef __ACTIVE_CALLBACKS_INTERFACES_H__
#define __ACTIVE_CALLBACKS_INTERFACES_H__
#include <memory>
namespace NSActive {
    enum class TaskState { EXECUTED_FAIL, EXECUTED_OK };
    struct IActiveCallBackExecutor {
        virtual ~IActiveCallBackExecutor() = default;
        virtual void update_state(TaskState) = 0;
    };

    struct IActiveCallBack {
        virtual ~IActiveCallBack() = default;
        virtual void
        execute(const std::shared_ptr<IActiveCallBackExecutor> &callback_interface) = 0;
    };

    struct IActive {
        virtual ~IActive() = default;
        virtual TaskState execute_task() = 0;
    };

} // namespace NSActive
#endif