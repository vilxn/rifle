#include <iostream>
#include <random>

#include "raylib.h"
#include "src/ecs/EntityComponentSystem.h"

namespace XERN {
    struct Transform {
        Vector2 position;
    };

    class RenderingSystem : public System {
    public:
        void Render() {
            for (auto const& entity : m_entities) {
                auto& transform = ECS::coordinator.GetComponent<Transform>(entity);

                DrawRectangleV(transform.position, {10, 10}, RED);
            }
        }
    };
}

int main() {
    ECS::coordinator.Init();
    ECS::coordinator.RegisterComponent<XERN::Transform>();
    auto renderingSystem = ECS::coordinator.RegisterSystem<XERN::RenderingSystem>();

    Signature signature;
    signature.set(ECS::coordinator.GetComponentType<XERN::Transform>());
    ECS::coordinator.SetSystemSignature<XERN::RenderingSystem>(signature);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> randPosition(0.0f, 600.0f);

    for (int i = 0; i < 10; i++) {
        auto entity = ECS::coordinator.CreateEntity();
        ECS::coordinator.AddComponent(
            entity,
            XERN::Transform{
                .position = {randPosition(generator), randPosition(generator)}
            }
        );
    }

    InitWindow(1200, 600, "Xern2D");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        renderingSystem->Render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}