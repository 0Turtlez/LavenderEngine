cmake_minimum_required(VERSION 3.10)
project(LavenderEngine)

set(CMAKE_CXX_STANDARD 17)

# Point to Homebrew's location on Apple Silicon
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Include personal libaray
include_directories(lib)
include_directories(include/glad/include)

# Find GLFW and OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Define Executable
add_executable(lavender main.cpp
        include/glad/src/glad.c
        lib/Scene/scene.cpp
        lib/Scene/scene.h
        lib/Object/object.cpp
        lib/Object/object.h
        lib/Renderer/Renderer.cpp
        lib/Renderer/Renderer.h
        lib/Camera/Camera.cpp
        lib/Camera/Camera.h
)

# Link Frameworks and Libraries to the 'lavender' target
find_library(OPENGL_LIB OpenGL REQUIRED)
find_library(GLUT_LIB GLUT REQUIRED)
target_link_libraries(lavender
        glfw
        "${OPENGL_LIB}"
)