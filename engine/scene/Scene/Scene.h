
//
// Created by Zachary on 3/3/26.
//

#ifndef LAVENDER_SCENE_H
#define LAVENDER_SCENE_H
#include <vector>
#include <sol/function.hpp>

#include "math/Color/Color.h"
#include "math/Transform/Transform.h"

// forward declare, temp fix, actually figure out the solution
namespace lavender::core { class Object; }

using namespace lavender::math;
using namespace lavender::core;

class Scene {
public:
    void start();           // Ran at start of program
    void update(float deltaTime);          // Ran every frame

    // Eventually add an overload that will create the object for each case of inputs
    Object* createAndAdd(int vertices, Color color, bool isFilled, float thickness, Transform transform);

    std::vector<Object*> objects;

private:

    sol::function luaUpdateFunc;

    // Update the count of vertexes of Object
    void updateVertexCount(lavender::core::Object* obj, int vertex);

};


#endif //LAVENDER_SCENE_H