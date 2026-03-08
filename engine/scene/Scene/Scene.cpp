//
// Created by Zachary on 3/3/26.
//

#include "Scene.h"
#include "core/Object/Object.h"

using namespace lavender::core;
using namespace lavender::math;
#ifndef PI
    #define PI 3.14159265358979323846
#endif


// Sets up Scene by pushing all Object data to Scene
Object* Scene::createAndAdd(int vertices, Color color, bool isFilled, float thickness, Transform transform) {
    Object* newObj = new Object(Object::createPolygon(vertices, color, isFilled, thickness, transform));
    objects.push_back(newObj);
    return newObj;
}

// Runs at start of program
void Scene::start() {
    auto result = Application::lua.script_file("assets/scripts/main_scene.lua");

    if (!result.valid()) {
        sol::error err = result;
        std::cerr << "LUA ERROR: " << err.what() << std::endl;
    }

    if (result.valid()) {
        sol::function luaStart = Application::lua["start"];
        luaStart(this);

        luaUpdateFunc = Application::lua["update"];
    }
}

// Ran every frame
void Scene::update(float deltaTime) {
    if (luaUpdateFunc.valid()) {
        luaUpdateFunc(deltaTime);
    }
}
