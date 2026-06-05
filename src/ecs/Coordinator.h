#ifndef XERN2D_COORDINATOR_H
#define XERN2D_COORDINATOR_H
#include <memory>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "../logger/Logger.h"


class Coordinator {
public:
    void Init() {
        m_entityManager = std::make_unique<EntityManager>();
        m_systemManager = std::make_unique<SystemManager>();
        m_componentManager = std::make_unique<ComponentManager>();

        XERN_INFO("Main ECS Coordinator is initialized")
    }

    Entity CreateEntity() {
        return m_entityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity) {
        m_entityManager->DestroyEntity(entity);
        m_componentManager->EntityDestroyed(entity);
        m_systemManager->EntityDestroyed(entity);
    }

    template<typename T>
    void RegisterComponent() {
        m_componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        m_componentManager->AddComponent(entity, component);

        auto signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentType<T>(), true);
        m_entityManager->SetSignature(entity, signature);

        m_systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        return m_componentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType() {
        return m_componentManager->GetComponentType<T>();
    }

    template<typename T>
    void RegisterSystem() {
        m_systemManager->RegisterSystem<T>();
    }

    template<typename T>
    std::shared_ptr<T> GetSystem() {
        return m_systemManager->GetSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature) {
        m_systemManager->SetSignature<T>(signature);
    }

private:
    std::unique_ptr<EntityManager> m_entityManager;
    std::unique_ptr<SystemManager> m_systemManager;
    std::unique_ptr<ComponentManager> m_componentManager;
};


#endif //XERN2D_COORDINATOR_H
