//  Zachary Davis
//  in asm1/main.cpp
//
//  Scene-Object-Data can and should be refactored into header
//  Structs Point, Color, Transform, Rotation, Scale, Object, Scene
//  Structs make up the storage of information needed to create, manipulate, and display polygons
//
//  Object-Init can be moved to separate class
//
//  animateShape should be refactored to separate class
//
//  update method and start method should be refactored to be called anywhere and overloaded
//
//  display and opengl initialization should be refactored to use VBO VAO and EBO to allow for better performance
//  display should also enable higher than 60fps

// in main, the goal is to be the trafic conductor that manages the order of execution
#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lib/Object/Object.h"
#include "lib/Scene/Scene.h"
#include "lib/Renderer/Renderer.h"
#include <iostream>


// Global Scene declare
Scene scene;

// Scales canvas to viewport to prevent shearing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "W" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, char** argv) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }
    // Sets GLFW version (CORE PROFILE 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(960, 540, "Lavender", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // Initial scene function call
    scene.start();

    // Time
    double pastTime = glfwGetTime();
    const double targetFrameRate = 60.0;
    const double timePerFrame = 1 / targetFrameRate;

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
    return 0;
}