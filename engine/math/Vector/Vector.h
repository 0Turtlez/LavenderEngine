//
// Created by Zachary on 3/5/26.
//

#ifndef LAVENDERENGINE_VECTOR_H
#define LAVENDERENGINE_VECTOR_H

#include <cmath>
#include <iterator>

namespace lavender::math {
    struct Vector2 {
        float x, y;

        Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}

        float length() const {
            return std::sqrt(x * x + y * y);
        };

        Vector2 normalize() const {
            float len = length();

            if (len > 0.0f) {
                return Vector2(x / len, y / len);
            }
            return Vector2(0,0);
        }
    };

    struct Vector3 {
        float x, y, z;
        Vector3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

        float length() const {
            return std::sqrt(x * x + y * y + z * z);
        };

        Vector3 normalize() const {
            float len = length();

            if (len > 0.0f) {
                return Vector3(x / len, y / len, z / len);
            }
            return Vector3(0,0,0);
        }
    };

    struct Vector4 {
        float x, y, z, w;
        Vector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) : x(_x), y(_y), z(_z), w(_w) {}

        float length() const {
            return std::sqrt(x * x + y * y + z * z + w * w);
        };

        Vector4 normalize() const {
            float len = length();

            if (len > 0.0f) {
                return Vector4(x / len, y / len, z / len, w / len);
            }
            return Vector4(0,0,0,0);
        }
    };

    class Vector {
    public:

    };
}
#endif //LAVENDERENGINE_VECTOR_H