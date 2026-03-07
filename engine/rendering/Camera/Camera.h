//
// Created by Zachary on 3/3/26.
//

#ifndef ASM1_CAMERA_H
#define ASM1_CAMERA_H
#include "math/Transform/Transform.h"

class Camera {
public:
    // Position Data, later once object is refactored to have the more seperation of visuals and logic
    // then just extend object,
    lavender::math::Transform position;
private:
};


#endif //ASM1_CAMERA_H