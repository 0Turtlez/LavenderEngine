//
// Created by Zachary on 3/3/26.
//

#include "Scene.h"
#ifndef PI
    #define PI 3.14159265358979323846
#endif


// Update the count of vertexes of Object
void Scene::updateVertexCount(Object* obj, int vertex) {
    // Minimum 3 vertex
    if (vertex < 3) {
        vertex = 3;
    }

    obj->points.clear();

    float angle_step = 360.0 / vertex;

    // Store the polygon data based on how many vertex the shape has
    for (int v = 0; v < vertex; v++) {
        float current_angle = v * angle_step;
        float radians = current_angle * (PI / 180.0f);

        Point point;
        point.x = cos(radians);
        point.y = sin(radians);
        obj->points.push_back(point);
    }
}

// Experimental: animation code that rotates, translates and scales polygons also updates vertex count
void Scene::animateShapes() {
    for (Object* object : objects) {
        object->rotation.x -= rotateSpeed;

        object->transform.x += moveSpeed;
        object->transform.y += moveSpeed;

        if (object->transform.x > 150.0f) {
            object->transform.x = -150.0f;
        }

        if (object->transform.y > 120.0f) {
            object->transform.y = -120.0f;
        }

        object->scale = Scale(object->scale.x - scaleSpeed, object->scale.y - scaleSpeed);

        if (object->scale.x < -10) {
            object->scale= Scale(10.0f, 10.0f);
        }

        if (frameCounter % 15 == 0) {
            int currentVertices = object->points.size();
            int nextVertices = currentVertices + 1;

            // update to min size when reach max size
            if (nextVertices > 12) {
                nextVertices = 3;
            }

            updateVertexCount(object, nextVertices);

        }
    }
}

// Sets up Scene by pushing all Object data to Scene
Object* Scene::createAndAdd(int vertices, Color color, bool isFilled, float thickness, Transform trans, Scale scale, Rotation rotation) {
    Object* newObj = new Object(Object::createPolygon(vertices, color, isFilled, thickness, trans, scale, rotation));
    objects.push_back(newObj);
    return newObj;
}

void Scene::update() {
    // Experimental Object manipulation
    animateShapes();
    frameCounter++;
}

// Runs at start of program
void Scene::start() {
    float borderThickness = 0.0f;
    const float shapeScale = 1.0f;

    // Triangle
    tri = createAndAdd(3, Color{0.0f, 0.0f, 0.5f}, false, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{210.0f});
    tri2 = createAndAdd(3, Color{1.0f, 0.0f, 0.0f}, true, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{210.0f});

    // Squares
    square = createAndAdd(4, Color{0.0f, 0.5f, 1.0f}, false, borderThickness ,Transform(), Scale(shapeScale, shapeScale), Rotation{45.0f});
    square2 = createAndAdd(4, Color{0.0f, 1.0f, 0.0f}, true, borderThickness ,Transform(), Scale(shapeScale, shapeScale), Rotation{45.0f});

    // Pentagons
    pen = createAndAdd(5, Color{0.0f, 0.5f, 0.5f}, false, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{90});
    pen2 = createAndAdd(5, Color{1.0f, 1.0f, 0.0f}, true, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{90.0f});

    // Hexagons
    hex = createAndAdd(6, Color{0.5f, 0.0f, 0.0f}, false, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{0.0f});
    hex2 = createAndAdd(6, Color{0.0f, 0.0f, 1.0f}, true, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{0.0f});

    // Heptagons
    hep = createAndAdd(7, Color{0.5f, 1.0f, 0.5f}, false, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{0.0f});
    hep2 = createAndAdd(7, Color{1.0f, 0.0f, 1.0f}, true, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{0.0f});

    // Octagons
    oct = createAndAdd(8, Color{0.5f, 0.5f, 0.0f}, false, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{0.0f});
    oct2 = createAndAdd(8, Color{0.0f, 1.0f, 1.0f}, true, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{0.0f});

    // Circles
    circle = createAndAdd(360, Color{1.0f, 0.5f, 0.5f}, false, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{0.0f});
    circle2 = createAndAdd(360, Color{1.0f, 1.0f, 0.5f}, true, borderThickness, Transform(10, 0), Scale(shapeScale, shapeScale), Rotation{0.0f});
    // Triangle
    tri->transform = Transform{-85, 75};
    tri2->transform = Transform{-55, 75};

    // Square
    square->transform = Transform{-15, 75};
    square2->transform = Transform{15, 75};

    // Pentagon
    pen->transform = Transform{55, 75};
    pen2->transform = Transform{85, 75};

    // Hex
    hex->transform = Transform{-85, 0};
    hex2->transform = Transform{-55, 0};

    // Hep
    hep->transform = Transform{-15, 0};
    hep2->transform = Transform{15, 0};

    // Oct
    oct->transform = Transform{55, 0};
    oct2->transform = Transform{85, 0};

    // Circle
    circle->transform = Transform{-15,  -75};
    circle2->transform = Transform{15, -75};

}