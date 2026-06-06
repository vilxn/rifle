cmake_minimum_required(VERSION 4.1)
project(Rifle C CXX)

set(CMAKE_CXX_STANDARD 23)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_subdirectory(libs/raylib-6.0)

add_executable(${PROJECT_NAME} main.cpp
        src/ecs/core.h
        src/ecs/ComponentArray.h
        src/ecs/ComponentManager.h
        src/ecs/EntityManager.h
        src/ecs/System.h
        src/ecs/SystemManager.h
        src/ecs/Coordinator.h
        src/ecs/EntityComponentSystem.h
        src/ecs/basicComponents/Transform.h
        src/ecs/EntityComponentSystem.cpp
        src/ecs/basicComponents/RigidBody.h
        src/logger/Logger.cpp
        src/logger/Logger.h
        src/rendering/RenderingSystem.cpp
        src/rendering/RenderingSystem.h
        src/rendering/TerrarianRenderSystem.cpp
        src/rendering/TerrarianRenderSystem.h
        src/components/HexMap.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

#target_link_libraries(${PROJECT_NAME} PRIVATE
#        raylib
#        opengl32
#        gdi32
#        winmm)
