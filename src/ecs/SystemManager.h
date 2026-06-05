#ifndef XERN2D_SYSTEMMANAGER_H
#define XERN2D_SYSTEMMANAGER_H
#include <cassert>
#include <memory>
#include <unordered_map>

#include "core.h"
#include "System.h"


class SystemManager {
public:
    template<typename T>
    void RegisterSystem() {
        const char* typeName = typeid(T).name();

        assert(!m_systems.contains(typeName) && "This system already registered");

        auto system = std::make_shared<T>();
        m_systems[typeName] = std::static_pointer_cast<System>(system);
    }

    template<typename T>
    void SetSignature(Signature signature) {
        const char* typeName = typeid(T).name();

        assert(m_systems.contains(typeName) && "System registration required");

        m_signatures[typeName] = signature;
    }

    void EntityDestroyed(const Entity entity) {
        for (auto const& pair : m_systems) {
            auto system = pair.second;
            system->m_entities.erase(entity);
        }
    }

    void EntitySignatureChanged(const Entity entity, const Signature entitySignature) {
        for (auto const& pair : m_systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& signature = m_signatures[type];

            if ((entitySignature & signature) == signature) {
                system->m_entities.insert(entity);
            } else {
                system->m_entities.erase(entity);
            }
        }
    }

    template<typename T>
    std::shared_ptr<T> GetSystem() {
        const char* typeName = typeid(T).name();
        assert(m_systems.contains(typeName) && "System registration required");
        return std::static_pointer_cast<T>(m_systems[typeName]);
    }

private:
    std::unordered_map<const char*, Signature> m_signatures;
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems;
};


#endif //XERN2D_SYSTEMMANAGER_H
