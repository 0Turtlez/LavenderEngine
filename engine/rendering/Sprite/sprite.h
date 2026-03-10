//
// Created by miste on 3/9/2026.
//

#ifndef LAVENDERENGINE_SPRITE_H
#define LAVENDERENGINE_SPRITE_H
#include "core/Object/Object.h"
#include "rendering/Texture/texture.h"

namespace lavender::rendering {
    class Sprite : public Object{
    public:
        Texture* texture;

        Sprite(Texture* texture, Color color = Color())
        : Object(createQuadPoints(), color, true), texture(texture){}

        float uvCoords[8] = {0,0, 1,0, 1,1, 0,1};

    private:
        static std::vector<Point> createQuadPoints() {
            return {
                {0.0f, 1.0f}, // Top Left
                {1.0f, 1.0f}, // Top Right
                {1.0f, 0.0f}, // Bottom Right
                {0.0f, 0.0f}, // Bottom Left

            };
        }
    };
}


#endif //LAVENDERENGINE_SPRITE_H