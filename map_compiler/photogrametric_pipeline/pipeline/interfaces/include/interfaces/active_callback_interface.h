#ifndef __ACTIVE_CALLBACKS_INTERFACES_H__
#define __ACTIVE_CALLBACKS_INTERFACES_H__
#include <memory>
namespace NSActive {
    enum class TaskState { EXECUTED_FAIL, EXECUTED_OK };

    struct IActiveCallBackExecutor {
        virtual ~IActiveCallBackExecutor() = default;
        virtual void update_state(TaskState) = 0;
        virtual TaskState get_state() const = 0;
        virtual void notify() = 0;
    };

    struct IActive {
        using IActiveCallBackExecutorShared = std::shared_ptr<IActiveCallBackExecutor>;
        virtual ~IActive() = default;
        virtual void set_callback(const IActiveCallBackExecutorShared &callback_interface) = 0;
        virtual const IActiveCallBackExecutorShared &get_callback() const = 0;
        virtual void execute_task() = 0;
        virtual void notify_with_callback() = 0;
        virtual int get_task_id() const = 0;
    };

} // namespace NSActive
#endif