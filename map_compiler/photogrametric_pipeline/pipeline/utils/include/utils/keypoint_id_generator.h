#ifndef __KEYPOINT_ID_GENERATOR_H__
#define __KEYPOINT_ID_GENERATOR_H__
#include <cstdint>
#include <memory>
namespace NSFeatureExtraction {
    class KeyPointIdGenerator {

        public:
        using KeyPointID = std::uint32_t;
        static KeyPointIdGenerator &getInstance();
        KeyPointID getNewKeyPointId() noexcept;

        private:
        KeyPointIdGenerator();
        ~KeyPointIdGenerator();
        KeyPointID current_keypoint_id_ = KeyPointID();
        static KeyPointIdGenerator *instance_ptr_;
    };
} // namespace NSFeatureExtraction

#endif