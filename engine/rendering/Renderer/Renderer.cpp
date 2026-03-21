//
// Created by Zachary on 3/3/26.
//
#define GL_SILENCE_DEPRECATION
#include "Renderer.h"
#include "core/Object/Object.h"
#include "math/MathUtils/MathUtils.h"

#include "glad/glad.h"
#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>

#include "rendering/Sprite/sprite.h"

using namespace lavender::core;
using namespace lavender::math;

unsigned int Renderer::vertexShader = 0;
unsigned int Renderer::fragmentShader = 0;
unsigned int Renderer::shaderProgram = 0;
unsigned int Renderer::VAO = 0;
unsigned int Renderer::VBO = 0;
unsigned int Renderer::EBO = 0;
unsigned int Renderer::quadVAO = 0;
unsigned int Renderer::quadVBO = 0;

float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f,  // bottom left
   -0.5f,  0.5f, 0.0f   // top left
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,  // first Triangle
    1, 2, 3   // second Triangle
};

void Renderer::setupRenderer() {
    setUpShaders();
    setUpVertexObjects(vertices, sizeof(vertices), indices, sizeof(indices));
    setUpQuadVertexObjects();
}
void Renderer::drawScene(Scene &scene) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Gather points into master buffer
    std::vector<Point> masterBuffer;
    for (Object* object : scene.objects) {
        if (object == nullptr) {
            continue;
        }

        if (dynamic_cast<Sprite*>(object) == nullptr) {
            masterBuffer.insert(masterBuffer.end(), object->points.begin(), object->points.end());
        }
    }
    // Bind State
    glUseProgram(shaderProgram);

    // Cache shader uniform location
    int offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    int scaleLoc = glGetUniformLocation(shaderProgram, "scale");
    int colorLoc = glGetUniformLocation(shaderProgram, "objColor");
    int aspectLoc = glGetUniformLocation(shaderProgram, "aspectRatio");
    int rotationLoc = glGetUniformLocation(shaderProgram, "rotation");
    int useTextureLoc = glGetUniformLocation(shaderProgram, "useTexture");

    glUniform1f(aspectLoc, 960.0f / 540.0f);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Upload all data to GPU in one call
    glBufferData(GL_ARRAY_BUFFER, masterBuffer.size() * sizeof(Point), masterBuffer.data(), GL_DYNAMIC_DRAW);


    // Draw calls into master buffer
    int currentOffset = 0;
    for (Object* object : scene.objects) {
        if (object == nullptr) {
            continue;
        }
        Sprite* spr = dynamic_cast<Sprite*>(object);
        if (spr) {
            glUniform1i(useTextureLoc, 1);
            drawSprite(*spr, offsetLoc, scaleLoc, colorLoc, rotationLoc, aspectLoc);
        }
        else {
            glUniform1i(useTextureLoc, 0);

            glBindVertexArray(VAO);

            glUniform2f(offsetLoc, object->transform.position.x / 100.0f, object->transform.position.y / 100.0f);
            glUniform2f(scaleLoc, object->transform.scale.x / 100.0f, object->transform.scale.y / 100.0f);
            glUniform4f(colorLoc, object->color.r, object->color.g, object->color.b, 1.0f);

            float rotationRad = object->transform.rotation.z * (PI / 180.0f);
            glUniform1f(rotationLoc, rotationRad);
            if (object->isFilled) {
                glDrawArrays(GL_TRIANGLE_FAN,  currentOffset, (GLsizei)object->points.size());
            } else {
                glDrawArrays(GL_LINE_LOOP, currentOffset, (GLsizei)object->points.size());
            }

            currentOffset += object->points.size();
        }
    }

    // Unbind state
    glBindVertexArray(0);
}

void Renderer::shutdownRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

void Renderer::setUpShaders() {
    // Vertex
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // Compile check
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }

    // Fragment
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Compile Check
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Renderer::setUpVertexObjects(float vertices[], size_t sizeVertices, unsigned int indices[], size_t sizeIndices) {
    // Generate VAO VBO and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and set VBOs
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeVertices, vertices, GL_DYNAMIC_DRAW);

    // Bind and set EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, indices, GL_STATIC_DRAW);

    // Config vertex attributes
    // Update to 3 when I start doing 3D graphics
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterward so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::setUpQuadVertexObjects() {

    // Enable Alpha Blending for transparent PNGs
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Define quad
    float quadVertices[] = {
        // Pos      // Tex
        -0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    // Position attribute (Location 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture Coordinate attribute (Location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

// Draws objects polygon
// later refactor to need just the polygon data, saves memory and speeds up draw
void Renderer::drawObject(const Object &obj) {
    glUseProgram(shaderProgram);

    glUniform2f(glGetUniformLocation(shaderProgram, "offset"), obj.transform.position.x / 100.0f, obj.transform.position.y / 100.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "scale"), obj.transform.position.x / 100.0f);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, obj.points.size() * sizeof(Point), obj.points.data(), GL_DYNAMIC_DRAW);

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "objColor");
    glUniform4f(vertexColorLocation, obj.color.r, obj.color.g, obj.color.b, 1.0f);

    if (obj.isFilled) {
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)obj.points.size());
    } else {
        glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)obj.points.size());
    }

    glBindVertexArray(0);
    // // Save current coordinate system state
    // glPushMatrix();
    //
    // // Apply Scale Rotate Transform each point and add to the polygon
    // // Reverse order
    // glTranslatef(obj.position.x, obj.position.y, 0.0f);
    // glRotatef(obj.rotation.z, 0.0f, 0.0f, 1.0f);
    // glScalef(obj.scale.x, obj.scale.y, 1.0f);
    //
    // // Set Style
    // glLineWidth(obj.borderThickness);
    // glColor3f(obj.color.r, obj.color.g, obj.color.b);
    //
    // // Set fill mode
    // if (obj.isFilled) {
    //     glBegin(GL_POLYGON);
    // } else {
    //     glBegin(GL_LINE_LOOP);
    // }
    //
    // // Apply style for each point on the vertex
    // for (const auto& p : obj.points) {
    //     glVertex2f(p.x, p.y);
    // }
    //
    // glEnd();
    //
    // glPopMatrix();
}

void Renderer::drawSprite(const Sprite &sprite, int offsetLoc, int scaleLoc, int colorLoc, int rotationLoc,
    int aspectLoc) {

    // 1. Set Uniforms
    glUniform2f(offsetLoc, sprite.transform.position.x / 100.0f, sprite.transform.position.y / 100.0f);
    glUniform2f(scaleLoc, sprite.transform.scale.x / 100.0f, sprite.transform.scale.y / 100.0f);
    glUniform4f(colorLoc, sprite.color.r, sprite.color.g, sprite.color.b, sprite.color.a);

    float rotationRad = sprite.transform.rotation.z * (PI / 180.0f);
    glUniform1f(rotationLoc, rotationRad);

    // 2. Bind Texture
    if (sprite.texture) {
        sprite.texture->bind(0); // Bind to slot 0
    }

    // 3. Draw the static quad
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
