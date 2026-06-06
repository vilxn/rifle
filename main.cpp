#include "raylib.h"
#include "src/ecs/EntityComponentSystem.h"
#include "src/rendering/RenderingSystem.h"
#include "src/rendering/TerrarianRenderSystem.h"

using namespace ECS;

int main() {
    gECS.Init();
    RegisterBasicComponents();
    RegisterBasicSystems();

    auto renderingSystem = gECS.GetSystem<RenderingSystem>();
    auto terrarianRender = gECS.GetSystem<TerrarianRenderSystem>();

    SetWindowState(FLAG_MSAA_4X_HINT);
    InitWindow(1200, 600, "Rifle");
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
