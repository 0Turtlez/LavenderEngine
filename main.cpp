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
#include <GLUT/glut.h>
#include "lib/Object/Object.h"
#include "lib/Scene/Scene.h"
#include "lib/Renderer/Renderer.h"


#pragma region Object-Init
// Global Scene declare
Scene scene;
#pragma endregion Object-Init


// Updates screen 60 fps
void timer(int value) {

    // Calls update code every 60fps
    scene.update();

    // Triggers redraw
    glutPostRedisplay();
    // Waits 16ms per update
    glutTimerFunc(16, timer, value);
}

void display() {
    Renderer::drawScene(scene);
}
// Scales canvas to viewport to prevent shearing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set aspect of window based on width and height
    float aspect = (float)width / (float)height;
    if (aspect >= 1.0f) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Davis");

    // Set background to dark gray
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    scene.start();

    // Assign display func
    glutDisplayFunc(display);
    // Assign window reshape func
    glutReshapeFunc(reshape);
    // Assign timer and start it
    glutTimerFunc(0, timer, 0);

    // Start app
    glutMainLoop();
    return 0;
}