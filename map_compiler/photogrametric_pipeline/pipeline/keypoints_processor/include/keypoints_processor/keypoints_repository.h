#pragma once
#include <memory>
#include <mutex>
#include <tuple>
#include <unordered_map>
namespace NSFeatureExtraction {
    /**
     * @brief      Singleton class repository for
     * multithreading access
     */

    class KeyPointsRepository {
        public:
        using KeyPoint = std::uint32_t;
        using ImageId = std::uint32_t;
        using KeyPointId = std::tuple<KeyPoint, ImageId>;
        virtual ~KeyPointsRepository() = default;

        static KeyPointsRepository &getInstance() {
            std::call_once(m_once, []() { m_instance.reset(new T); });
            return *m_instance;
        }

        template <typename... Args>
        static KeyPointsRepository &getInstance2nd(Args &&... args) {
            std::call_once(m_once, [&]() { instance_.reset(new T(std::forward<Args>(args)...)); });
            return *m_instance;
        }
        void addExternalReference(const KeyPointId &external_keypoint_id);

        private:
        KeyPointsRepository(const KeyPointsRepository &) = delete;
        KeyPointsRepository &operator=(const KeyPointsRepository &) = delete;

        KeyPointsRepository() = default;

        static std::unique_ptr<KeyPointsRepository> instance_;
        static std::once_flag once_;
        std::unordered_map<KeyPointId, std::unordered_set<KeyPoint>>
    };
    std::unique_ptr<KeyPointsRepository> KeyPointsRepository::instance_ = nullptr;
    std::once_flag KeyPointsRepository::once_;
} // namespace NSFeatureExtraction