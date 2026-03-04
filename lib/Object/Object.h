//
// Created by Zachary on 3/3/26.
//

#ifndef ASM1_OBJECT_H
#define ASM1_OBJECT_H
#include <vector>


// 2D point of a drawn polygon, with default constructor of position 0,0
struct Point {
    float x, y;

    Point(float _x = 0, float _y = 0) : x(_x), y(_y) {}
};

// RBG color
struct Color {
    float r, g, b;

    Color(float _r = 1, float _g = 1, float _b = 1) : r(_r), g(_g), b(_b) {}
};

// 2D point of the center of the Object
struct Transform {
    float x, y;

    Transform(float _x = 0, float _y = 0) : x(_x), y(_y) {}
};

// Rotation Value
// z = theta in degrees
struct Rotation {
    float z = 0;

    Rotation(float _x = 0) : z(_x) {}
};

// 2D scaling values
struct Scale {
    float x , y ;
    Scale(float _x = 1, float _y = 1) : x(_x), y(_y) {}
};

// Object holding 2D Object data
class Object {
public:
    // Later refactor the polygon information to a sprite or visual struct
    std::vector<Point> points;
    Color color;
    bool isFilled;
    float borderThickness;

    // Position Data
    Transform worldPosition;
    Transform position;
    Scale scale;
    Rotation rotation;

    // Constructor
    Object(
        const std::vector<Point> &_points,
        Color _color = Color(),
        bool _isFilled = false,
        float _borderThickness = 0.0f,

        Transform _transform = Transform(),
        Scale _scale = Scale(),
        Rotation _rotation = Rotation()
    );

    static Object createPolygon(int vertex, Color color, bool isFilled, float borderThickness, Transform transform, Scale scale, Rotation rotation);

private:
};
#endif //ASM1_OBJECT_H