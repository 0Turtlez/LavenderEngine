//
// Created by Zachary on 3/5/26.
//

#include "MathUtils.h"

#include <algorithm>
#include <cmath>

namespace lavender::math {
    float MathUtils::sinf(float x) {
        return std::sin(x);
    }

    float MathUtils::cosf(float x) {
        return std::cos(x);
    }

    float MathUtils::tanf(float x) {
        return std::tan(x);
    }

    float MathUtils::asinf(float x) {
        return std::asin(x);
    }

    float MathUtils::acosf(float x) {
        return std::acos(x);
    }

    float MathUtils::atanf(float x) {
        return std::atan(x);
    }

    float MathUtils::atan2f(float x, float y) {
        return std::atan2(x, y);
    }

    float MathUtils::toRadians(float degrees) {
        return degrees * (PI / 180.0);
    }

    float MathUtils::toDegrees(float radians) {
        return radians * (180.0 / PI);
    }

    float MathUtils::clamp(float value, float min, float max) {
        return std::clamp(value, min, max);
    }

    float MathUtils::lerp(float start, float end, float time) {
        return start + (end - start) * time;
    }

    float MathUtils::sqrt(float x) {
        return std::sqrt(x);
    }

    float MathUtils::invSqrt(float x) {
        return 1.0f / std::sqrt(x);
    }

    float MathUtils::pow(float val, float power) {
        return std::pow(val, power);
    }

    float MathUtils::abs(float val) {
        return std::abs(val);
    }

    float MathUtils::fmod(float x, float y) {
        return std::fmod(x, y);
    }

    float MathUtils::floor(float x) {
        return std::floor(x);
    }

    float MathUtils::ceil(float x) {
        return std::ceil(x);
    }

    float MathUtils::round(float x) {
        return std::round(x);
    }

    float MathUtils::trunc(float x) {
        return std::trunc(x);
    }

    float MathUtils::max(float a, float b) {
        return std::max(a, b);
    }

    float MathUtils::min(float a, float b) {
        return std::min(a, b);
    }

    bool MathUtils::floatIsEqual(float x, float y) {
        const float EPSILON = 0.00001;
        return std::abs(x - y) < EPSILON;
    }
}
