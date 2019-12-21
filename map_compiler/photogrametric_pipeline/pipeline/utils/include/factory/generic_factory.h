#ifndef __GENERIC_FACTORY__
#define __GENERIC_FACTORY__
#include "factory_base.h"
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace NSPipelineUtils {

    class Factory {
        using MapFactory =
            std::unordered_map<std::string, std::function<std::unique_ptr<FactoryBase>()>>;

        public:
        static Factory &getInstance() {
            if (FactoryPtr == nullptr && IsNullPtr) {
                createFactoryInstance();
            }
            return *FactoryPtr;
        }

        void registerFactoryFunction(
            const std::string &aStringKey,
            std::function<std::unique_ptr<FactoryBase>()> aClassFactoryFunctor) {

            FactoryRegistryMap->insert({aStringKey, aClassFactoryFunctor});
        }

        std::size_t getInstancesCount() { return FactoryRegistryMap->size(); }

        bool isEmpty() const { return FactoryRegistryMap->empty(); }

        std::unique_ptr<FactoryBase> getInstancePtr(const std::string &aClassName) {
            std::unique_ptr<FactoryBase> instance_ptr = nullptr;
            const auto iter = FactoryRegistryMap->find(aClassName);
            if (iter != FactoryRegistryMap->end()) {
                instance_ptr = (iter->second)();
            }
            return instance_ptr;
        }

        void releaseResources() { FactoryRegistryMap->clear(); }

        static void releaseSingleton() {
            IsNullPtr = true;
            FactoryPtr = nullptr;
        }

        private:
        ~Factory() {}
        Factory() : FactoryRegistryMap(std::make_unique<MapFactory>()) {}
        Factory operator=(const Factory &) = delete;
        Factory(const Factory &) = delete;

        static void createFactoryInstance() {
            static Factory factory;
            FactoryPtr = &factory;
            IsNullPtr = false;
        }
        std::unique_ptr<MapFactory> FactoryRegistryMap;

        static Factory *FactoryPtr;
        static bool IsNullPtr;
    };

    Factory *Factory::FactoryPtr = nullptr;
    bool Factory::IsNullPtr = true;

} // namespace NSPipelineUtils
#endif