//
// Created by Zachary on 3/6/26.
//

#ifndef LAVENDERENGINE_APPLICATION_H
#define LAVENDERENGINE_APPLICATION_H
#include <string>
#include <utility>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sol/sol.hpp>



#include "scene/Scene/Scene.h"


namespace lavender::core {
    struct Application {
    public:
        // Window name
        std::string name;
        // Window Dimensions
        int width{}, height{};
        // Lua scripting state
        static sol::state lua;
        // Current scene
        // TODO: make this variable to allow scene swapping
        static Scene scene;
        // Constructor for Application
        // move is used because it is only copied once so the reference is moved instead
        Application(std::string _name, int _width, int _height) :
            name(std::move(_name)), width(_width), height(_height)
        {}


        // Runs the application
        // TODO: Figure why to make static or not
        void run();


    private:
        // Time
        static double pastTime;
        static double targetFrameRate;
        static double timePerFrame;

        // Static window reference
        static GLFWwindow* window;

        static void emscripten_callback();
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mainLoop();
        static void mainLoopStep();
        static void setupGlad();
        static void setupGLFW();

        void setupImGui();

        static void setupLua();
    };
}


#endif //LAVENDERENGINE_APPLICATION_H