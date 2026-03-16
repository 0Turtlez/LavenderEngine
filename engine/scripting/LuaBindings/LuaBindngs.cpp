//
// Created by miste on 3/7/2026.
//

#include "LuaBindngs.h"

#include "audio/Audio/AudioEngine.h"
#include "math/Vector/Vector.h"
#include "math/Transform/Transform.h"
#include "core/Object/Object.h"
#include "input/keyboard/Keyboard.h"
#include "math/Random/Random.h"
#include "math/MathUtils/MathUtils.h"
#include "rendering/Sprite/sprite.h"
#include "rendering/Texture/texture.h"
using namespace lavender::math;
using namespace lavender::input;
using namespace lavender::audio;
using namespace lavender::rendering;
void LuaBindngs::setLuaBindings(sol::state &lua) {
    lua.open_libraries(
        sol::lib::base,
        sol::lib::math,
        sol::lib::package,
        sol::lib::table
    );

#pragma region Vectors
    lua.new_usertype<Vector2>("Vector2",
        "x", &Vector2::x,
        "y", &Vector2::y,

        "length", &Vector2::length,
        "normalize", &Vector2::normalize
    );

    lua.new_usertype<Vector3>("Vector3",
        sol::constructors<Vector3(), Vector3(float, float, float)>(),
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
        sol::constructors<Rotation(), Rotation(float, float, float)>(),
       "x", &Rotation::x,
       "y", &Rotation::y,
       "z", &Rotation::z
    );

    lua.new_usertype<Scale>("Scale",
        sol::constructors<Scale(), Scale(float, float, float)>(),
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
    sol::table randomTable = lua.create_named_table("random");

    randomTable.set_function("int", &Random::random_int);
    randomTable.set_function("float", &Random::random_float);
    randomTable.set_function("double", &Random::random_float);
    randomTable.set_function("bool", &Random::random_bool);
    randomTable.set_function("vector2", &Random::random_vector2);
    randomTable.set_function("vector3", &Random::random_vector3);
    randomTable.set_function("vector4", &Random::random_vector4);
    randomTable.set_function("unit_vector2", &Random::random_unit_vector2);
    randomTable.set_function("unit_vector3", &Random::random_unit_vector3);
    randomTable.set_function("unit_vector4", &Random::random_unit_vector4);
    randomTable.set_function("color", &Random::random_color);
    randomTable.set_function("deviation", &Random::random_deviation);

    // These will take more work
    // randomTable.set_function("shuffleVector", &Random::shuffle_vector);
    // randomTable.set_function("randomElement", &Random::random_element);

#pragma endregion Random
#pragma region Math
    sol::table mathTable = lua.create_named_table("math");
    // Cos sin tangent
    mathTable.set_function("sin", &MathUtils::sinf);
    mathTable.set_function("cos", &MathUtils::cosf);
    mathTable.set_function("tan", &MathUtils::tanf);
    mathTable.set_function("asin", &MathUtils::asinf);
    mathTable.set_function("acos", &MathUtils::acosf);
    mathTable.set_function("atan", &MathUtils::atanf);
    mathTable.set_function("atan2", &MathUtils::atan2f);

    // Convert Rad <-> Deg
    mathTable.set_function("to_radians", &MathUtils::toRadians);
    mathTable.set_function("to_degrees", &MathUtils::toDegrees);

    // Misc math functions
    mathTable.set_function("clamp", &MathUtils::clamp);
    mathTable.set_function("lerp", &MathUtils::lerp);
    mathTable.set_function("sqrt", &MathUtils::sqrt);
    mathTable.set_function("inv_sqrt", &MathUtils::invSqrt);
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
    mathTable.set_function("float_is_equal", &MathUtils::floatIsEqual);
#pragma endregion Math
#pragma region Sprite-Control
    lua.new_usertype<Color>("Color",
    sol::constructors<Color(), Color(float, float, float)>(),
        "r", &Color::r,
        "g", &Color::g,
        "b", &Color::b,

        // constants for faster completion
        "white", sol::var(Color(1.0f, 1.0f, 1.0f)),
        "black", sol::var(Color(0.0f, 0.0f, 0.0f)),
        "red",   sol::var(Color(1.0f, 0.0f, 0.0f)),
        "green", sol::var(Color(0.0f, 1.0f, 0.0f)),
        "blue",  sol::var(Color(0.0f, 0.0f, 1.0f))
    );
#pragma endregion Sprite-Control
#pragma region Scene-Manangment
    lua.new_usertype<Object>("Object",
        "color", &Object::color,
        "transform", &Object::transform,
        "is_filled", &Object::isFilled,
        "texture", &Object::texture
        // We can't easily bind 'points' yet because it's a std::vector of custom structs
    );

    lua.new_usertype<Scene>("Scene",
        "objects", &Scene::objects,
        "create_and_add",  &Scene::createAndAdd,

        "add_sprite", [](Scene& scene, std::string path, Transform transform) {
            auto* tex = new Texture(path);
            auto* spr = new Sprite(tex);
            spr->transform = transform;
            scene.objects.push_back(spr);
            return spr;
        }
    );
#pragma endregion Scene-Manangment
#pragma region Input
lua.new_enum("Key",
        "Unknown", KeyCode::Unknown,
        "A", KeyCode::A, "B", KeyCode::B, "C", KeyCode::C, "D", KeyCode::D,
        "E", KeyCode::E, "F", KeyCode::F, "G", KeyCode::G, "H", KeyCode::H,
        "I", KeyCode::I, "J", KeyCode::J, "K", KeyCode::K, "L", KeyCode::L,
        "M", KeyCode::M, "N", KeyCode::N, "O", KeyCode::O, "P", KeyCode::P,
        "Q", KeyCode::Q, "R", KeyCode::R, "S", KeyCode::S, "T", KeyCode::T,
        "U", KeyCode::U, "V", KeyCode::V, "W", KeyCode::W, "X", KeyCode::X,
        "Y", KeyCode::Y, "Z", KeyCode::Z,

        "D0", KeyCode::D0, "D1", KeyCode::D1, "D2", KeyCode::D2, "D3", KeyCode::D3,
        "D4", KeyCode::D4, "D5", KeyCode::D5, "D6", KeyCode::D6, "D7", KeyCode::D7,
        "D8", KeyCode::D8, "D9", KeyCode::D9,

        "Escape", KeyCode::Escape, "Enter", KeyCode::Enter,
        "Tab", KeyCode::Tab, "Backspace", KeyCode::Backspace,
        "Insert", KeyCode::Insert, "Delete", KeyCode::Delete,

        "Right", KeyCode::Right, "Left", KeyCode::Left,
        "Up", KeyCode::Up, "Down", KeyCode::Down,

        "LeftShift", KeyCode::LeftShift, "LeftControl", KeyCode::LeftControl,
        "LeftAlt", KeyCode::LeftAlt, "LeftSuper", KeyCode::LeftSuper,
        "RightShift", KeyCode::RightShift, "RightControl", KeyCode::RightControl,
        "RightAlt", KeyCode::RightAlt, "RightSuper", KeyCode::RightSuper,

        "Space", KeyCode::Space
    );

    sol::table keyboardTable = lua.create_named_table("keyboard");

    keyboardTable.set_function("is_down", &Keyboard::isKeyDown);
#pragma endregion Input
#pragma region Audio
    sol::table audioTable = lua.create_named_table("audio");
    audioTable.set_function("play", &AudioEngine::playSound);
#pragma endregion Audio
#pragma region Rendering
    lua.new_usertype<Texture>("texture",
        sol::constructors<Texture(std::string)>()
    );

    lua.new_usertype<Sprite>("Sprite",
        sol::constructors<Sprite(Texture*, Color)>(),
        "Texture", &Sprite::texture,
        sol::base_classes, sol::bases<Object>()
    );
#pragma endregion Rendering
}
