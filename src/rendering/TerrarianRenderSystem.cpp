#include "TerrarianRenderSystem.h"

#include "raylib.h"
#include <cmath>

Vector3 Hex_Corner(Vector3 center, float size, int i){
    float angle_deg = 60 * i - 30;
    float angle_rad = angle_deg * DEG2RAD;
    return Vector3{
        center.x + size * std::cos(angle_rad),
        0.0f,
        center.y + size * std::sin(angle_rad)
    };
}

void TerrarianRenderSystem::Render() {
    DrawPlane(Vector3(0), Vector2(10, 10), GREEN);

    for (int i = 0; i < 6; i++){
        Vector3 c = Vector3(0);
        DrawLine3D(Hex_Corner(c, 10, i), Hex_Corner(c, 10, (i + 1) % 6), BLACK);
    }
}
