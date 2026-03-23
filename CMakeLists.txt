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
include_directories(include/miniaudio)
include_directories(include/stb_image)

# Find GLFW and OpenGL, skipped for Emscripten
if (NOT EMSCRIPTEN)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
endif ()
find_package(PkgConfig REQUIRED)
pkg_check_modules(LUAJIT REQUIRED IMPORTED_TARGET luajit)
find_package(sol2 CONFIG REQUIRED)

add_compile_definitions(SOL_LUAJIT=1)
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
        include/miniaudio/miniaudio.h
        engine/audio/Audio/AudioEngine.cpp
        engine/audio/Audio/AudioEngine.h
        engine/rendering/Sprite/sprite.cpp
        engine/rendering/Sprite/sprite.h
        engine/rendering/Texture/texture.cpp
        engine/rendering/Texture/texture.h
        include/stb_image/stb_image.h
)

target_include_directories(lavender PRIVATE
        ${LUA_INCLUDE_DIR}
        ${LUAJIT_INCLUDE_DIRS}
)
# Link Frameworks and Libraries to the 'lavender' target
target_link_libraries(lavender
        PRIVATE
        sol2::sol2
        PkgConfig::LUAJIT
        imgui::imgui
)


if (NOT EMSCRIPTEN)
    target_link_libraries(lavender
        PRIVATE
        glfw
        OpenGL::GL
    )
endif ()

if (WIN32)
    target_link_libraries(lavender PRIVATE winmm)
endif ()

if(APPLE)
    target_link_libraries(lavender PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()

if (EMSCRIPTEN)
    set_target_properties(lavender PROPERTIES
            OUTPUT_NAME "index"
            SUFFIX ".html"
    )

    # Optimization Flags for Release Build
    # -Oz: Aggressive optimization for size
    # --closure 1: Minifies the JavaScript glue code
    target_compile_options(lavender PRIVATE "-Oz")
    # Use Emscripten's built-in GLFW3 port and allow memory growth
    target_link_options(lavender PRIVATE
            "-Oz"
            "--closure 1"
            "SHELL:--shell-file ${CMAKE_CURRENT_SOURCE_DIR}/shell.html"
            "--minify 1"
            "-sUSE_GLFW=3"
            "-sWASM=1"
            "-sALLOW_MEMORY_GROWTH=1"
            "-sMIN_WEBGL_VERSION=2"
            "-sMAX_WEBGL_VERSION=2"
            # Preload the assets folder into the virtual file system
            "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets@/assets"
    )
endif()
# Add assets folder
# TODO: refactor to allow project directories, temporary copy
add_custom_command(TARGET lavender POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rm -rf "$<TARGET_FILE_DIR:lavender>/assets"
#        COMMENT "Deleting old assets build"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:lavender>/assets"
        COMMENT "Copying assets to the build output directory..."
)