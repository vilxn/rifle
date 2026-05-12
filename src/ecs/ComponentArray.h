#ifndef XERN2D_COMPONENTARRAY_H
#define XERN2D_COMPONENTARRAY_H

#include <cassert>
#include <unordered_map>

#include "core.h"

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray {
public:
    void InsertData(Entity entity, T component) {
        assert(!m_entityToIndexMap.contains(entity) && "Component already added to this entity");

        size_t newIndex = m_size;
        m_components[newIndex] = component;

        m_entityToIndexMap[entity] = newIndex;
        m_indexToEntityMap[newIndex] = entity;

        m_size++;
    }

    void RemoveData(Entity entity) {
        assert(m_entityToIndexMap.contains(entity) && "This entity doesn't have this component");

        size_t indexOfLastEntity = m_size - 1;
        size_t indexOfRemovedEntity = m_entityToIndexMap[entity];

        m_components[indexOfRemovedEntity] = m_components[indexOfLastEntity];

        Entity entityOfLastElement = m_indexToEntityMap[indexOfLastEntity];
        m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(indexOfLastEntity);

        m_size--;
    }

    T& GetData(Entity entity) {
        assert(m_entityToIndexMap.contains(entity) && "This entity doesn't have this component");

        return m_components[m_entityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override {
        if (m_entityToIndexMap.contains(entity)) {
            RemoveData(entity);
        }
    }

private:
    std::array<T, MAX_ENTITIES> m_components;
    std::unordered_map<Entity, size_t> m_entityToIndexMap;
    std::unordered_map<size_t, Entity> m_indexToEntityMap;
    size_t m_size{};
};


#endif
