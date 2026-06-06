#ifndef RIFLE_TERRARIANRENDERSYSTEM_H
#define RIFLE_TERRARIANRENDERSYSTEM_H

#include "../ecs/System.h"
#include "raylib.h"

Vector3 Hex_Corner(Vector3 center, float size, int i);


class TerrarianRenderSystem : public System{
public:
    void Render();
};


#endif //RIFLE_TERRARIANRENDERSYSTEM_H
