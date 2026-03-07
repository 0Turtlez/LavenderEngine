//
// Created by Zachary on 3/6/26.
//

#include "Application.h"

#include <iostream>
#include <ostream>

#include "rendering/Renderer/Renderer.h"


Scene Application::scene;
double Application::pastTime = 0.0;
double Application::targetFrameRate = 60.0;
double Application::timePerFrame = 1 / targetFrameRate;
GLFWwindow* Application::window = nullptr;

void Application::run() {
    // std::cout<<"run()"<< std::endl;
    setupGLFW();
    setupGlad();

    // Setup time
    pastTime = glfwGetTime();

    // Initial scene function call
    scene.start();

    mainLoop();
}

void Application::mainLoop() {
    Renderer::setupRenderer();

    // Display Loop
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - pastTime;

        processInput(window);

        if (deltaTime >= timePerFrame) {
            // Update scene by delta time to target fps
            scene.update(deltaTime);

            // Render
            // Set background to dark gray
            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Renderer::drawScene(scene);

            // Swap buffers and poll
            glfwSwapBuffers(window);
            glfwPollEvents();
            pastTime = currentTime;
        }

        glfwPollEvents();
    }

    Renderer::shutdownRenderer();
    // Close Window
    glfwTerminate();
}

void Application::setupGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize!" << std::endl;
        // Crash App
    }
    // Sets GLFW version (CORE PROFILE 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(960, 540, "Lavender", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        // Crash App
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Application::framebuffer_size_callback);

}

void Application::setupGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // Crash app
    }
}

// Scales canvas to viewport to prevent shearing
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "W" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}