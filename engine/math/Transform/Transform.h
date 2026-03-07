//
// Created by Zachary on 3/5/26.
//

#ifndef LAVENDERENGINE_TRANSFORM_H
#define LAVENDERENGINE_TRANSFORM_H
#include "../engine/math/Vector/Vector.h"


namespace lavender::math {
    // Rotation Value
    // z = theta in degrees
    struct Rotation {
        float x, y, z;

        Rotation(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}
    };

    // 3D scaling values
    struct Scale {
        float x , y, z;
        Scale(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}
    };

    // 2D point of the center of the Object
    struct Transform {
        Vector3 position;
        Rotation rotation;
        Scale scale;
    };
}
#endif //LAVENDERENGINE_TRANSFORM_H