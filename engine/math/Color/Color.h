//
// Created by Zachary on 3/5/26.
//

#ifndef LAVENDERENGINE_COLOR_H
#define LAVENDERENGINE_COLOR_H


namespace lavender::math {
    struct Color {
        float r, g, b, a;
        Color(float _r = 255.0f, float _g = 255.0f, float _b = 255.0f, float _a = 1.0f)
        :
        r(_r), g(_g), b(_b), a(_a)
        {
        }
    };

    // class Color {
    // };}
}

#endif //LAVENDERENGINE_COLOR_H