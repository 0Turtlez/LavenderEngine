//
// Created by Zachary on 3/3/26.
//

#ifndef ASM1_RENDERER_H
#define ASM1_RENDERER_H
#include "../engine/scene/Scene/Scene.h"
#include "rendering/Sprite/sprite.h"

using lavender::core::Object;
using lavender::rendering::Sprite;

class Renderer {
public:
    static void setupRenderer();

    static void drawScene(Scene &scene);
    static void shutdownRenderer();
private:
    static unsigned int vertexShader , fragmentShader, shaderProgram;
    static unsigned int quadVAO, quadVBO;
    static unsigned int VBO, VAO, EBO;

    static void setUpShaders();

    static void setUpVertexObjects(float vertices[], size_t sizeVertices, unsigned int indices[], size_t sizeIndices);
    static void setUpQuadVertexObjects();
    static void drawObject(const Object& obj);
    static void drawSprite(const Sprite& sprite, int offsetLoc, int scaleLoc, int colorLoc, int rotationLoc, int aspectLoc);


    static inline const char *vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTextureCoord;

        out vec2 TextureCoord;

        uniform vec2 offset;
        uniform vec2 scale;
        uniform float aspectRatio;
        uniform float rotation;

        void main() {
            // Scale
            vec2 scaledPos = aPos * scale;

            // Roation 2D, later update to allow for 3D
            float cosTheta = cos(rotation);
            float sinTheta = sin(rotation);
            vec2 rotatedPos = vec2(
                scaledPos.x * cosTheta - scaledPos.y * sinTheta,
                scaledPos.x * sinTheta + scaledPos.y * cosTheta
            );

            // Offset
            vec2 finalPos = rotatedPos + offset;

            // Apply scale and offset manually for now
            gl_Position = vec4(finalPos.x / aspectRatio, finalPos.y, 0.0, 1.0);
            TextureCoord = aTextureCoord;
        }
    )glsl";
    static inline const char *fragmentShaderSource = R"glsl(
        #version 330 core
        out vec4 FragColor;

        in vec2 TextureCoord;

        uniform vec4 objColor;
        uniform sampler2D image;
        uniform bool useTexture;

        void main() {
            if (useTexture) {
                FragColor = texture(image, TextureCoord) * objColor;
            } else {
                FragColor = objColor;
            }
        }
    )glsl";
};


#endif //ASM1_RENDERER_H