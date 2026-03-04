//
// Created by Zachary on 3/3/26.
//

#ifndef ASM1_SCENE_H
#define ASM1_SCENE_H
#include <vector>
#include "Object/Object.h"

class Scene {
public:
    void start();           // Ran at start of program
    void update();          // Ran every frame
    void animateShapes();   // Experimental logic

    std::vector<Object*> objects;

private:
    Object *tri, *tri2, *square, *square2, *pen, *pen2,
    *hex, *hex2, *hep, *hep2, *oct, *oct2, *circle, *circle2;

    // private state variables
    float moveSpeed = 0.5f;
    float rotateSpeed = 1.0f;
    float scaleSpeed = 0.1f;
    int frameCounter = 0;

    // Eventually add an overload that will create the object for each case of inputs
    Object* createAndAdd(int vertices, Color color, bool isFilled, float thickness, Transform trans, Scale scale, Rotation rotation);
    // Update the count of vertexes of Object
    void updateVertexCount(Object* obj, int vertex);
};


#endif //ASM1_SCENE_H