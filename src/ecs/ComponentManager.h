#ifndef XERN2D_COMPONENTMANAGER_H
#define XERN2D_COMPONENTMANAGER_H
#include <memory>
#include <unordered_map>

#include "ComponentArray.h"
#include "core.h"


class ComponentManager {
public:
    template<typename T>
    void RegisterComponent() {
        const char* typeName = typeid(T).name();

        assert(!m_componentTypes.contains(typeName) && "Component already registered");

        m_componentTypes[typeName] = m_nextComponentType;
        m_componentArrays[typeName] = std::make_shared<ComponentArray<T>>();

        m_nextComponentType++;
    }

    template<typename T>
    ComponentType GetComponentType() {
        const char* typeName = typeid(T).name();
        assert(m_componentTypes.contains(typeName) && "There is no such component");

        return m_componentTypes[typeName];
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T& GetComponent (Entity entity) {
        return GetComponentArray<T>()->GetData(entity);
    }

    void EntityDestroyed(Entity entity) {
        for (auto const& pair : m_componentArrays) {
            auto const& componentArray= pair.second;
            componentArray->EntityDestroyed(entity);
        }
    }


private:
    std::unordered_map<const char*, ComponentType> m_componentTypes;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;

    ComponentType m_nextComponentType{};

    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray() {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.contains(typeName) && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
    }
};


#endif
