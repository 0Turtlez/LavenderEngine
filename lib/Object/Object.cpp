//
// Created by Zachary on 3/3/26.
//

#include "Object.h"
#include <cmath>

#ifndef PI
    #define PI 3.14159265358979323846
#endif


Object::Object(
    const std::vector<Point> &_points, Color _color, bool _isFilled, float _borderThickness, Transform _transform, Scale _scale, Rotation _rotation) :
    points(_points),
    color(_color),
    isFilled(_isFilled),
    borderThickness(_borderThickness),
    position(_transform),
    scale(_scale),
    rotation(_rotation) {

}

// Create Object and initialize values
Object Object::createPolygon(int vertex, Color color, bool isFilled, float borderThickness, Transform transform, Scale scale, Rotation rotation) {
    std::vector<Point> genPoints;

    float angle_step = 360.0 / vertex;

    // Store the polygon data based on how many vertex the shape has
    for (int v = 0; v < vertex; v++) {
        float current_angle = v * angle_step;
        float radians = current_angle * (PI / 180.0f);

        Point point;
        point.x = cos(radians);
        point.y = sin(radians);
        genPoints.push_back(point);
    }

    return Object(genPoints, color, isFilled, borderThickness, transform, scale, rotation);

}