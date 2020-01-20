#include <utils/keypoint_id_generator.h>

namespace NSFeatureExtraction {
    KeyPointIdGenerator *KeyPointIdGenerator::instance_ptr_ = nullptr;
    KeyPointIdGenerator::KeyPointIdGenerator() {}
    KeyPointIdGenerator::~KeyPointIdGenerator() {}
    KeyPointIdGenerator &KeyPointIdGenerator::getInstance() {

        if (instance_ptr_ == nullptr) {
            static KeyPointIdGenerator instance;
            instance_ptr_ = &instance;
        }

        return *instance_ptr_;
    }

    KeyPointIdGenerator::KeyPointID KeyPointIdGenerator::getNewKeyPointId() noexcept {
        return current_keypoint_id_++;
    }

} // namespace NSFeatureExtraction