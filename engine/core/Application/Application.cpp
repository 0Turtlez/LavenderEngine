//
// Created by Zachary on 3/6/26.
//

#include "Application.h"

#include <chrono>
#include <iostream>
#include <ostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "audio/Audio/AudioEngine.h"
#include "core/Object/Object.h"
#include "input/keyboard/Keyboard.h"
#include "input/keycodes/KeyCodes.h"
#include "rendering/Renderer/Renderer.h"
#include "scripting/LuaBindings/LuaBindngs.h"


using namespace lavender::core;
using namespace lavender::input;

// Initialize header variables
sol::state Application::lua;
Scene Application::scene;
double Application::pastTime = 0.0;
double Application::targetFrameRate = 144.0; // TODO: Expose this to lua
double Application::timePerFrame = 1 / targetFrameRate;
GLFWwindow* Application::window = nullptr;


void Application::emscripten_callback() {
    Application::mainLoopStep();
}

// Scales canvas to viewport to prevent shearing
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::mainLoop() {
    Renderer::setupRenderer();

#ifdef __EMSCRIPTEN__
    // 0 = match browser fps
    // 1 = simulate infinite loop
    emscripten_set_main_loop(emscripten_callback, 0, 1);
#else
    // Display Loop
    while (!glfwWindowShouldClose(window)) {

        mainLoopStep();
    }

    Renderer::shutdownRenderer();
    // Close Window
    glfwTerminate();
#endif
}

void Application::mainLoopStep() {
    double currentTime = glfwGetTime();
    // Calculate delta time
    double deltaTime = currentTime - pastTime;
    pastTime = currentTime;

    // if delta time is too high, cap it
    if (deltaTime > 0.25) deltaTime = 0.25;

    // Elapsed time since last frame
    static double accumulator = 0.0;
    accumulator += deltaTime;

    //
    while (accumulator >= timePerFrame) {
        scene.update(timePerFrame); // Use the fixed step here
        accumulator -= timePerFrame;
    }

    // Calls once per frame
    // Set bg color default
    // TODO: either expose to api or make constant
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Renderer::drawScene(scene);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::setupGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // Crash app
    }
}

void Application::setupGLFW() {
    // Tries to set up GLFW if it fails then terminate
    // Common causes for error, glad is not accessible, GLFW is not on system
    if (!glfwInit()) {
        std::cerr << "Failed to initialize!" << std::endl;
        glfwTerminate();
    }

#ifdef __EMSCRIPTEN__
    // Used 3.0 OpenGL Embedded System because of crashes but,
    // https://www.khronos.org/opengles/
    // TODO: Upgrade to 3.2
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
    // Sets GLFW version (CORE PROFILE 3.3)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

#ifdef __APPLE__
    // Apple mac GLFW opengl profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // TODO: Expose window control to lua, title, size, auto display mode(windowed, windowed full screen, full screen)
    window = glfwCreateWindow(960, 540, "Lavender", nullptr, nullptr);

    // Checks window creation success
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
    }

    // Assign window to glfw
    glfwMakeContextCurrent(window);
    // Tracks key inputs from GLFW window
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        // Get pressed key
        const KeyCode lavenderKey = glfwToLavenderKey(key);

        // Handle press and release to prepare for conversion to lavenderKeys
        if (action == GLFW_PRESS) {
            Keyboard::setKeyState(lavenderKey, true);
        } else if (action == GLFW_RELEASE) {
            Keyboard::setKeyState(lavenderKey, false);
        }
    });

    // Set the method that runs when updating window size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}

void Application::setupImGui() {

}

void Application::setupLua() {
    LuaBindngs::setLuaBindings(lua);
}

void Application::run() {
    setupGLFW();
    setupGlad();
    audio::AudioEngine::init();
    setupLua();

    // Setup time
    pastTime = glfwGetTime();

    // Initial scene function call
    scene.start();

    mainLoop();
    audio::AudioEngine::shutdown();
}
