cmake_minimum_required(VERSION 4.1)
project(asm1)

set(CMAKE_CXX_STANDARD 17)

# Point to Homebrew's location on Apple Silicon
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Include Glad headers
include_directories(glad/include)
include_directories(lib)

# Define the executable with BOTH main.cpp and glad.c
add_executable(asm1 main.cpp glad/src/glad.c
        lib/scene/scene.cpp
        lib/scene/scene.h
        lib/Object/object.cpp
        lib/Object/object.h
        lib/Renderer/Renderer.cpp
        lib/Renderer/Renderer.h
)

# Link Frameworks and Libraries to the 'asm1' target
find_library(OPENGL_LIB OpenGL REQUIRED)
find_library(GLUT_LIB GLUT REQUIRED)
target_link_libraries(asm1 glfw "${OPENGL_LIB}" "${GLUT_LIB}")