//
// Created by Zachary on 3/3/26.
//

#ifndef ASM1_RENDERER_H
#define ASM1_RENDERER_H
#include "Scene/Scene.h"


class Renderer {
public:
    static void drawScene(Scene &scene);
    static void shutdownRenderer();
private:
    static unsigned int vertexShader , fragmentShader, shaderProgram;
    static unsigned int VBO, VAO, EBO;
    static void setUpShaders();

    static void setUpVertexObjects(float vertices[], size_t sizeVertices, unsigned int indices[], size_t sizeIndices);

    static void drawObject(const Object& obj);


    static inline const char *vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )glsl";

    static inline const char *fragmentShaderSource = R"glsl(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 objColor;

        void main() {
            FragColor = objColor;
        }
    )glsl";
};


#endif //ASM1_RENDERER_H