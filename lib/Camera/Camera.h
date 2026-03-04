//
// Created by Zachary on 3/3/26.
//

#ifndef ASM1_CAMERA_H
#define ASM1_CAMERA_H
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


class Camera {
public:
    // Position Data, later once object is refactored to have the more seperation of visuals and logic
    // then just extend object,
    Transform worldPosition;
    Transform position;
    Scale scale;
    Rotation rotation;
private:
};


#endif //ASM1_CAMERA_H