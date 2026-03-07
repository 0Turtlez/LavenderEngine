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
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

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
)

if (WIN32)
    add_custom_command(TARGET lavender POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/ucrt64/bin/glfw3.dll"
        $<TARGET_FILE_DIR:lavender>)
endif ()


# Link Frameworks and Libraries to the 'lavender' target
target_link_libraries(lavender
        PRIVATE
        glfw
        OpenGL::GL
)