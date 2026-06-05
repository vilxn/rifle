#ifndef XERN2D_TRANSFORM_H
#define XERN2D_TRANSFORM_H
#include "raylib.h"

namespace ECS {
    struct Transform {
        Vector2 position{0.0f};
        Quaternion rotation{0.0f};
        Vector2 scale{1.0f, 1.0f};
    };
}

#endif //XERN2D_TRANSFORM_H
