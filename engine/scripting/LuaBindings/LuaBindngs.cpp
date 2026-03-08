//
// Created by miste on 3/7/2026.
//

#include "LuaBindngs.h"

#include "math/Vector/Vector.h"
#include "math/Transform/Transform.h"
#include "core/Object/Object.h"
#include "math/Random/Random.h"
#include "math/MathUtils/MathUtils.h"
using namespace lavender::math;

void LuaBindngs::setLuaBindings(sol::state &lua) {
    lua.open_libraries(
        sol::lib::base,
        sol::lib::math,
        sol::lib::package
    );

#pragma region Vectors
    lua.new_usertype<Vector2>("Vector2",
        "x", &Vector2::x,
        "y", &Vector2::y,

        "length", &Vector2::length,
        "normalize", &Vector2::normalize
    );

    lua.new_usertype<Vector3>("Vector3",
        "x", &Vector3::x,
        "y", &Vector3::y,
        "z", &Vector3::z,

        "length", &Vector3::length,
        "normalize", &Vector3::normalize
    );

    lua.new_usertype<Vector4>("Vector4",
        "x", &Vector4::x,
        "y", &Vector4::y,
        "z", &Vector4::z,
        "w", &Vector4::w,

        "length", &Vector4::length,
        "normalize", &Vector4::normalize
    );

#pragma endregion Vectors
#pragma region Transform-Control
    lua.new_usertype<Rotation>("Rotation",
       "x", &Rotation::x,
       "y", &Rotation::y,
       "z", &Rotation::z
    );

    lua.new_usertype<Scale>("Scale",
        "x", &Scale::x,
        "y", &Scale::y,
        "z", &Scale::z
    );

    lua.new_usertype<Transform>("Transform",
        sol::constructors<Transform()>(),
        "position", &Transform::position,
        "rotation", &Transform::rotation,
        "scale", &Transform::scale

        // Scale, positon and rotation  control methods

    );
#pragma endregion Transform-Control
#pragma region Random
    sol::table randomTable = lua.create_named_table("Random");

    randomTable.set_function("randomInt", &Random::random_int);
    randomTable.set_function("randomFloat", &Random::random_float);
    randomTable.set_function("randomDouble", &Random::random_float);
    randomTable.set_function("randomBool", &Random::random_bool);
    randomTable.set_function("randomVector2", &Random::random_vector2);
    randomTable.set_function("randomVector3", &Random::random_vector3);
    randomTable.set_function("randomVector4", &Random::random_vector4);
    randomTable.set_function("randomUnitVector2", &Random::random_unit_vector2);
    randomTable.set_function("randomUnitVector3", &Random::random_unit_vector3);
    randomTable.set_function("randomUnitVector4", &Random::random_unit_vector4);
    randomTable.set_function("randomColor", &Random::random_color);
    randomTable.set_function("randomDeviation", &Random::random_deviation);

    // These will take more work
    // randomTable.set_function("shuffleVector", &Random::shuffle_vector);
    // randomTable.set_function("randomElement", &Random::random_element);

#pragma endregion Random
#pragma region Math
    sol::table mathTable = lua.create_named_table("Math");
    // Cos sin tangent
    mathTable.set_function("sinf", &MathUtils::sinf);
    mathTable.set_function("cosf", &MathUtils::cosf);
    mathTable.set_function("tanf", &MathUtils::tanf);
    mathTable.set_function("asinf", &MathUtils::asinf);
    mathTable.set_function("acosf", &MathUtils::acosf);
    mathTable.set_function("atanf", &MathUtils::atanf);
    mathTable.set_function("atan2f", &MathUtils::atan2f);

    // Convert Rad <-> Deg
    mathTable.set_function("toRadians", &MathUtils::toRadians);
    mathTable.set_function("toDegrees", &MathUtils::toDegrees);

    // Misc math functions
    mathTable.set_function("clamp", &MathUtils::clamp);
    mathTable.set_function("lerp", &MathUtils::lerp);
    mathTable.set_function("sqrt", &MathUtils::sqrt);
    mathTable.set_function("invSqrt", &MathUtils::invSqrt);
    mathTable.set_function("pow", &MathUtils::pow);
    mathTable.set_function("abs", &MathUtils::abs);
    mathTable.set_function("fmod", &MathUtils::fmod);
    mathTable.set_function("floor", &MathUtils::floor);
    mathTable.set_function("ceil", &MathUtils::ceil);
    mathTable.set_function("round", &MathUtils::round);
    mathTable.set_function("trunc", &MathUtils::trunc);

    // Arrays/Iterables (See note below on why you might want to change these)
    mathTable.set_function("max", &MathUtils::max);
    mathTable.set_function("min", &MathUtils::min);

    // Float comparison
    mathTable.set_function("floatIsEqual", &MathUtils::floatIsEqual);
#pragma endregion Math
#pragma region Sprite-Control
    lua.new_usertype<Color>("Color",
    sol::constructors<Color(), Color(float, float, float)>(),
        "r", &Color::r,
        "g", &Color::g,
        "b", &Color::b
    );
#pragma endregion Sprite-Control
#pragma region Scene-Manangment
    lua.new_usertype<Object>("Object",
        "color", &Object::color,
        "transform", &Object::transform,
        "isFilled", &Object::isFilled
        // We can't easily bind 'points' yet because it's a std::vector of custom structs
    );

    lua.new_usertype<Scene>("Scene",
        "objects", &Scene::objects,
        "createAndAdd",  &Scene::createAndAdd
    );
#pragma endregion Scene-Manangment



}
