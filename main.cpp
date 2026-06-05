#include <iostream>
#include <random>

#include "raylib.h"
#include "src/ecs/EntityComponentSystem.h"
#include "src/ecs/basicComponents/RigidBody.h"
#include "src/ecs/basicComponents/Transform.h"
#include "src/logger/Logger.h"
#include "src/rendering/RenderingSystem.h"
#include "src/rendering/TerrarianRenderSystem.h"

using namespace ECS;

int main() {
    gECS.Init();
    RegisterBasicComponents();
    RegisterBasicSystems();

    auto renderingSystem = gECS.GetSystem<RenderingSystem>();
    auto terrarianRender = gECS.GetSystem<TerrarianRenderSystem>();

    InitWindow(1200, 600, "Xern2D");
    SetTargetFPS(60);

    auto camera = Camera3D();
    camera.fovy = 90;
    camera.position = Vector3(0, 10, 10);
    camera.target = Vector3(0, 0, 0);
    camera.up = Vector3(0, 1, 0);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        renderingSystem->Render();
        terrarianRender->Render();

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}