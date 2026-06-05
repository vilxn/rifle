#include "EntityComponentSystem.h"

#include "../rendering/RenderingSystem.h"
#include "../rendering/TerrarianRenderSystem.h"
#include "basicComponents/RigidBody.h"
#include "basicComponents/Transform.h"

void ECS::RegisterBasicComponents() {
    gECS.RegisterComponent<Transform>();
    gECS.RegisterComponent<RigidBody>();
}

void ECS::RegisterBasicSystems() {
    //RenderingSystem
    gECS.RegisterSystem<RenderingSystem>();

    Signature renderingSystemSignature;
    renderingSystemSignature.set(gECS.GetComponentType<ECS::Transform>());
    gECS.SetSystemSignature<RenderingSystem>(renderingSystemSignature);

    //TerrarianSystem
    gECS.RegisterSystem<TerrarianRenderSystem>();

    Signature terrarianRenderSignature;
    terrarianRenderSignature.set(gECS.GetComponentType<ECS::Transform>());
    gECS.SetSystemSignature<TerrarianRenderSystem>(terrarianRenderSignature);
}
