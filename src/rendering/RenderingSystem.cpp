//
// Created by user on 5/19/2026.
//

#include "RenderingSystem.h"

#include "../ecs/EntityComponentSystem.h"
#include "../ecs/basicComponents/Transform.h"

void RenderingSystem::Render() {
    for (auto entity : m_entities) {
        const auto& transform = ECS::gECS.GetComponent<ECS::Transform>(entity);
        DrawCircleV(transform.position, 20.0f, BLUE);
    }
}
