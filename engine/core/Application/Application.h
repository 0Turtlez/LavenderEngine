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

#include "scene/Scene/Scene.h"


namespace lavender::core {
    struct Application {
    public:
        std::string name;
        int width{}, height{};

        Application(std::string _name, int _width, int _height) :
            name(std::move(_name)), width(_width), height(_height)
        {}

        void run();


    private:
        static Scene scene;


        // Time
        static double pastTime;
        static  double targetFrameRate;
        static double timePerFrame;

        static GLFWwindow* window;

        static void mainLoop();
        static void setupGLFW();
        static void setupGlad();
        // Scales canvas to viewport to prevent shearing
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        // Handle input
        static void processInput(GLFWwindow *window);


    };
}


#endif //LAVENDERENGINE_APPLICATION_H