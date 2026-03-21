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

#include "core/Application/Application.h"
using namespace lavender::core;

int main(int argc, char** argv) {
    // Creates an application instance then runs it
    // TODO: Refactor to give lua control of application managment
    Application application = Application("Lavender", 500, 540);
    application.run();

    return 0;
}