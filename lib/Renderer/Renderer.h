//
// Created by Zachary on 3/3/26.
//

#ifndef ASM1_RENDERER_H
#define ASM1_RENDERER_H
#include "Scene/Scene.h"


class Renderer {
public:
    static void drawScene(Scene &scene);
private:
    static void drawObject(const Object& obj);
};


#endif //ASM1_RENDERER_H