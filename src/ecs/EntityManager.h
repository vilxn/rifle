#ifndef XERN2D_ENTITYMANAGER_H
#define XERN2D_ENTITYMANAGER_H
#include <array>
#include <cassert>
#include <queue>

#include "core.h"


class EntityManager {
public:
    EntityManager() {
        for (Entity i = 0; i < MAX_ENTITIES; i++) {
            m_availableEntities.push(i);
        }
    }

    Entity CreateEntity() {
        assert(m_livingEntityCount < MAX_ENTITIES && "Too many entities");

        Entity id = m_availableEntities.front();
        m_availableEntities.pop();
        m_livingEntityCount++;

        return id;
    }

    void DestroyEntity(Entity entity) {
        assert(m_livingEntityCount > 0 && "There is no entity left");

        m_signatures[entity].reset();
        m_availableEntities.push(entity);
        m_livingEntityCount--;
    }

    void SetSignature(Entity entity, Signature signature) {
        assert(entity < MAX_ENTITIES && "Entity is out of range");

        m_signatures[entity] = signature;
    }

    Signature GetSignature(Entity entity) const{
        assert(entity < MAX_ENTITIES && "Entity is out of range");

        return m_signatures[entity];
    }

private:
    std::queue<Entity> m_availableEntities;

    std::array<Signature, MAX_ENTITIES> m_signatures;

    uint32_t m_livingEntityCount{};
};


#endif //XERN2D_ENTITYMANAGER_H
