//
// Created by Zachary on 3/5/26.
//

#ifndef LAVENDERENGINE_MATHUTILS_H
#define LAVENDERENGINE_MATHUTILS_H
#define PI 3.14159265358979323846
#define E  2.71828182845904523536
#define TAU (2 * PI)

namespace lavender::math{
    class MathUtils {
        public
        :
        // Cos sin tangent; decide if i want teh inputs to be deg or radians
        static float sinf(float x);
        static float cosf(float x);
        static float tanf(float x);
        static float asinf(float x);
        static float acosf(float x);
        static float atanf(float x);
        static float atan2f(float x, float y);
        // Convert Rad <-> Deg
        static float toRadians(float degrees);
        static float toDegrees(float radians);

        // Misc math functions, alot of these are in prep for scripting abstraction
        static float clamp(float value, float min, float max);
        static float lerp(float start, float end, float time);
        static float sqrt(float x);
        static float invSqrt(float x); //inverse square root? wth is that
        static float pow(float val, float power);
        static float abs(float val);
        static float fmod(float x, float y); // also dont know what this is
        static float floor(float x);
        static float ceil(float x);
        static float round(float x);
        static float trunc(float x);
        // gonna have to get creative if I want these to be more than just floats
        static float max(float vals[]);
        static float min(float vals[]);
        // all the other excel like functions average, median, etc
        static bool floatIsEqual(float x, float y); // maybe epsilon input might just hard code it

        // Radian to degrees
        // Square root
        // PI constant
        // Eulers number
        // Pretty much every math library call should come from here, if there is a need for c math it should actually just be a function or abstraction here?
    };
}


#endif //LAVENDERENGINE_MATHUTILS_H