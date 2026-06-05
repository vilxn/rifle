#ifndef XERN2D_RIGIDBODY_H
#define XERN2D_RIGIDBODY_H
#include "raylib.h"

namespace ECS {
    struct RigidBody {
        Vector2 velocity{0.0f};
        float mass{0.0f};
    };
}

#endif //XERN2D_RIGIDBODY_H
