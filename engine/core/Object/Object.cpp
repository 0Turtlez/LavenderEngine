//
// Created by Zachary on 3/3/26.
//

#include "Object.h"
#include <cmath>

#ifndef PI
    #define PI 3.14159265358979323846
#endif

using namespace lavender::core;
Object::Object(
    const std::vector<Point> &_points, Color _color, bool _isFilled, float _borderThickness, Transform _transform, Scale _scale, Rotation _rotation) :
    points(_points),
    color(_color),
    isFilled(_isFilled),
    borderThickness(_borderThickness),
    transform(_transform)
{

}

// Create Object and initialize values
Object Object::createPolygon(int vertex, Color color, bool isFilled, float borderThickness, Transform transform) {
    std::vector<Point> genPoints;

    float angle_step = 360.0 / vertex;

    float starting_angle = (vertex % 2 == 0) ? (180.0f / vertex) : 90.0f;

    // Store the polygon data based on how many vertex the shape has
    for (int v = 0; v < vertex; v++) {
        float current_angle = starting_angle + (v * angle_step);
        float radians = current_angle * (PI / 180.0f);

        Point point;
        point.x = cos(radians);
        point.y = sin(radians);
        genPoints.push_back(point);
    }

    return Object(genPoints, color, isFilled, borderThickness, transform);

}