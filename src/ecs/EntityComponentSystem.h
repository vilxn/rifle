#pragma once
#include "Coordinator.h"

namespace ECS {
    inline Coordinator gECS;

    void RegisterBasicComponents();

    void RegisterBasicSystems();
}
