#include "graphics/texture.hpp"
#include <png.h>
#include <jpeglib.h>

namespace m3d {
    Texture::Texture() :
    m_width(0),
    m_height(0),
    m_path("") { /* do nothing */ }

    Texture::~Texture() {
        C3D_TexDelete(&m_texture);
    }

    bool Texture::loadFromFile(std::string t_filename) {

        return true;
    }

    int Texture::getWidth() {
    return m_width;
    }

    int Texture::getHeight() {
        return m_height;
    }

    std::string Texture::getPath() {
        return m_path;
    }

    C3D_Tex& Texture::getTexture() {
        return m_texture;
    }

    m3d::Texture& Texture::operator=(m3d::Texture& rhs) {
        if(this == &rhs) return *this;

        m_width = rhs.getWidth();
        m_height = rhs.getHeight();
        m_path = rhs.getPath();
        C3D_TexDelete(&m_texture);
        m_texture = rhs.getTexture();

        return *this;
    }
} /* m3d */
