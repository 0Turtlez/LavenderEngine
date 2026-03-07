//
// Created by Zachary on 3/5/26.
//

#ifndef LAVENDERENGINE_RANDOM_H
#define LAVENDERENGINE_RANDOM_H

#include <random>
#include <algorithm>

#include "math/Color/Color.h"
#include "math/Vector/Vector.h"

namespace lavender::math {
    class Random {
    public:
        // Random data types
        static int random_int(int min, int max);
        static float random_float(float min, float max);
        static char random_char(char min, char max);
        static bool random_bool();

        // Random Vectors with min and max
        static Vector2 random_vector2(float min, float max);
        static Vector3 random_vector3(float min, float max);
        static Vector4 random_vector4(float min, float max);

        // random unit vectors
        static Vector2 random_unit_vector2();
        static Vector3 random_unit_vector3();
        static Vector4 random_unit_vector4();

        // Radom Color control
        static Color random_color();

        // Shuffles items in generic vector of any type
        template<typename T>
        static void shuffle_vector(std::vector<T>& vector) {
            std::shuffle(vector.begin(), vector.end(), get_random());
        };

        // Selects random item from vector list
        template<typename T>
        static const T& random_element(std::vector<T>& vector) {
            return vector[random_int(0, static_cast<int>(vector.size()))];
        }

        // Selects from a random deviation from base
        static float random_deviation(float base, float deviation);

        // Gives a random probability roll, lower value means lower success
        static bool roll_chance(float probability);

        // later implement seeding
        // Later impplement random generic for custom data types

    private:
        static std::mt19937& get_random() {
            static std::random_device random_device;
            static std::mt19937 generator(random_device());
            return generator;
        };
    };
}



#endif //LAVENDERENGINE_RANDOM_H
