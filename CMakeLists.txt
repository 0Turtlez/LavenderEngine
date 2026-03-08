cmake_minimum_required(VERSION 3.10)
project(LavenderEngine)
set(CMAKE_CXX_STANDARD 17)

if(APPLE)
    # Point to Homebrew's location on Apple Silicon
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif ()
# Include personal libaray
include_directories(engine)
include_directories(include/glad/include)

# Find GLFW and OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(sol2 CONFIG REQUIRED)

# Define Executable
add_executable(lavender main.cpp
        include/glad/src/glad.c
        engine/scene/Scene/scene.cpp
        engine/scene/Scene/scene.h
        engine/core/Object/Object.cpp
        engine/core/Object/Object.h
        engine/Rendering/Renderer/Renderer.cpp
        engine/Rendering/Renderer/Renderer.h
        engine/Rendering/Camera/Camera.cpp
        engine/Rendering/Camera/Camera.h
        engine/input/keyboard/Keyboard.cpp
        engine/input/keyboard/Keyboard.h
        engine/math/MathUtils/MathUtils.cpp
        engine/math/MathUtils/MathUtils.h
        engine/math/Vector/Vector.cpp
        engine/math/Vector/Vector.h
        engine/math/Transform/Transform.cpp
        engine/math/Transform/Transform.h
        engine/math/Random/Random.cpp
        engine/math/Random/Random.h
        engine/math/Color/Color.cpp
        engine/math/Color/Color.h
        engine/math/Matrix/Matrix.cpp
        engine/math/Matrix/Matrix.h
        engine/math/MathUtils/MathUtils.h
        engine/core/Application/Application.cpp
        engine/core/Application/Application.h
        engine/input/keycodes/KeyCodes.cpp
        engine/input/keycodes/KeyCodes.h
        engine/scripting/LuaBindings/LuaBindngs.cpp
        engine/scripting/LuaBindings/LuaBindngs.h
)

# Link Frameworks and Libraries to the 'lavender' target
target_link_libraries(lavender
        PRIVATE
        glfw
        OpenGL::GL
        sol2::sol2
        unofficial::lua::lua
)