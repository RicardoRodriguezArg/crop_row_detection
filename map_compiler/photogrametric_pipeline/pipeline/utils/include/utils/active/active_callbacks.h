#ifndef __ACTIVE_CALLBACKS_H__
#define __ACTIVE_CALLBACKS_H__
#include <interfaces/active_callback_interface.h>

namespace NSActive {

    struct ActiveCallBack : public IActiveCallBack {
        ActiveCallBack(const std::shared_ptr<IActive> &object_ptr);

        ~ActiveCallBack() = default;

        void execute(const std::shared_ptr<IActiveCallBackExecutor> &callback_interface) override {
            const auto &result = object->execute_task();
            callback_interface->update_state(result);
        }

        const std::shared_ptr<IActive> &object;
    };
} // namespace NSActive
#endif