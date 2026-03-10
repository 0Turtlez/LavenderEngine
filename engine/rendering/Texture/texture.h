//
// Created by miste on 3/9/2026.
//

#ifndef LAVENDERENGINE_TEXTURE_H
#define LAVENDERENGINE_TEXTURE_H

#include <string>

namespace lavender::rendering {
    class Texture {
    public:
        Texture(): m_RendererID(0), m_Width(0), m_Height(0) {}
        Texture(const std::string& path);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        inline int getWidth() const { return m_Width; }
        inline int getHeight() const { return m_Height; }
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        int m_Width, m_Height, m_BPP;
    };
}


#endif //LAVENDERENGINE_TEXTURE_H