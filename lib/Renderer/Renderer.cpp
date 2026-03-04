//
// Created by Zachary on 3/3/26.
//
#define GL_SILENCE_DEPRECATION
#include "Renderer.h"
#include <GLUT/glut.h>
#ifndef PI
    #define PI 3.14159265358979323846
#endif


void Renderer::drawScene(Scene &scene) {
    glClear(GL_COLOR_BUFFER_BIT);

    // For each Object in Scene draw Object
    for (Object* object : scene.objects) {
        if (object == nullptr) {
            continue;
        }

        drawObject(*object);
    }


    glutSwapBuffers();
}

// Draws objects polygon
// later refactor to need just the polygon data, saves memory and speeds up draw
void Renderer::drawObject(const Object &obj) {
    glLineWidth(obj.borderThickness);
    glColor3f(obj.color.r, obj.color.g, obj.color.b);

    if (obj.isFilled) {
        glBegin(GL_POLYGON);
    } else {
        glBegin(GL_LINE_LOOP);
    }
    // Scale Rotate Transform each point and add to the polygon
    // Refactor to use built-in functions for SRT
    // glTranslatef
    // glRotatef
    // glScalef
    for (const auto& p : obj.points) {
        float point_x = p.x;
        float point_y = p.y;

        // Scale
        point_x *= obj.scale.x * 0.01;
        point_y *= obj.scale.y * 0.01;

        // Rotate
        float angle = obj.rotation.x * (PI / 180.0f);
        float rotated_x = (point_x * cos(angle)) - (point_y * sin(angle));
        float rotated_y = (point_x * sin(angle)) + (point_y * cos(angle));

        point_x = rotated_x;
        point_y = rotated_y;

        // Transform
        point_x += obj.transform.x * 0.01;
        point_y += obj.transform.y * 0.01;

        glVertex2f(point_x, point_y);
    }
    glEnd();
}
