#include "graphics/drawables/sprite.hpp"
#include <iostream>

namespace m3d {
    Sprite::Sprite() :
            m_posX(0),
            m_posY(0),
            m_width(0),
            m_height(0),
            m_changed(true),
            m_stretch(false),
            m_repeat(false),
            m_opacity(1.0f) { /* do nothing */ }

    Sprite::~Sprite() {
        linearFree(m_internalVertices);
        linearFree(m_elementData);
    }

    void Sprite::setXPosition(int t_x) {
        m_posX = t_x;
        m_changed = true;
    }

    int Sprite::getXPosition() {
        return m_posX;
    }

    void Sprite::setYPosition(int t_y) {
        m_posY = t_y;
        m_changed = true;
    }

    int Sprite::getYPosition() {
        return m_posY;
    }

    void Sprite::setPosition(int t_x, int t_y) {
        m_posX = t_x;
        m_posY = t_y;
        m_changed = true;
    }

    void Sprite::setPosition(Vector2f t_vector) {
        m_posX = static_cast<int>(t_vector.u);
        m_posY = static_cast<int>(t_vector.v);
        m_changed = true;
    }

    void Sprite::moveX(int t_offset) {
        m_posX += t_offset;
        m_changed = true;
    }

    void Sprite::moveY(int t_offset) {
        m_posY += t_offset;
        m_changed = true;
    }

    void Sprite::move(int t_offsetX, int t_offsetY) {
        m_posX += t_offsetX;
        m_posY += t_offsetY;
        m_changed = true;
    }

    void Sprite::move(Vector2f t_vector) {
        m_posX += static_cast<int>(t_vector.u);
        m_posY += static_cast<int>(t_vector.v);
        m_changed = true;
    }

    void Sprite::setWidth(int t_width) {
        m_width = t_width;
        m_changed = true;
    }

    int Sprite::getWidth() {
        return m_width;
    }

    void Sprite::setHeight(int t_height) {
        m_height = t_height;
        m_changed = true;
    }

    int Sprite::getHeight() {
        return m_height;
    }

    void Sprite::setDimensions(int t_width, int t_height) {
        m_width = t_width;
        m_height = t_height;
        m_changed = true;
    }

    BoundingBox Sprite::getBoundingBox() {
        return m3d::BoundingBox(m_posX, m_posY, m_width, m_height);
    }

    void Sprite::setOpacity(float t_opacity) {
        m_opacity = t_opacity;
        m_changed = true;
    }

    float Sprite::getOpacity() {
        return m_opacity;
    }

    void Sprite::setTexture(Texture t_texture, bool t_autoresize) {
        m_texture = t_texture;

        if (t_autoresize) {
            m_width = t_texture.getWidth();
            m_height = t_texture.getHeight();
        }

        m_changed = true;
    }

    Texture& Sprite::getTexture() {
        return m_texture;
    }

    void Sprite::setTextureStretching(bool t_stretch) {
        m_stretch = t_stretch;
        m_changed = true;
    }

    bool Sprite::getTextureStretching() {
        return m_stretch;
    }

    void Sprite::setTextureRepeat(bool t_repeat) {
        m_repeat = t_repeat;
    }

    bool Sprite::getTextureRepeat() {
        return m_repeat;
    }

    void Sprite::draw(int, int, int, int) {
        if (m_changed) {
            m_changed = false;
            linearFree(m_internalVertices);
            linearFree(m_elementData);
            m_internalVertices = static_cast<m3d::InternalTexturedVertex*>(linearAlloc(4 * sizeof(m3d::InternalTexturedVertex)));
            m_elementData = static_cast<s16*>(linearAlloc(6 * sizeof(s16)));

            // since sprites are always rectangular, we can hardcode the vertices
            if (m_stretch) {
                m_internalVertices[0] = (m3d::InternalTexturedVertex) { {m_posX, m_posY, 0.5f}, {0.0f, 0.0f} };
                m_internalVertices[1] = (m3d::InternalTexturedVertex) { {m_posX, m_posY + m_height, 0.5f}, {0.0f, 1.0f} };
                m_internalVertices[2] = (m3d::InternalTexturedVertex) { {m_posX + m_width, m_posY + m_height, 0.5f}, {1.0f, 1.0f} };
                m_internalVertices[3] = (m3d::InternalTexturedVertex) { {m_posX + m_width, m_posY, 0.5f}, {1.0f, 0.0f} };
            } else {
                float v = (float) m_width  / (float) m_texture.getWidth();
                float u = (float) m_height / (float) m_texture.getHeight();

                m_internalVertices[0] = (m3d::InternalTexturedVertex) { {m_posX, m_posY, 0.5f}, {0.0f, 0.0f} };
                m_internalVertices[1] = (m3d::InternalTexturedVertex) { {m_posX, m_posY + m_height, 0.5f}, {0.0f, u} };
                m_internalVertices[2] = (m3d::InternalTexturedVertex) { {m_posX + m_width, m_posY + m_height, 0.5f}, {v, u} };
                m_internalVertices[3] = (m3d::InternalTexturedVertex) { {m_posX + m_width, m_posY, 0.5f}, {v, 0.0f} };
            }

            m_elementData[0] = 0;
            m_elementData[1] = 1;
            m_elementData[2] = 2;
            m_elementData[3] = 2;
            m_elementData[4] = 3;
            m_elementData[5] = 0;
        }

        // there be dragons
        C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
        AttrInfo_Init(attrInfo);
        AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // position
        AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // texture coordinates

        C3D_BufInfo* bufInfo = C3D_GetBufInfo();
        BufInfo_Init(bufInfo);
        BufInfo_Add(bufInfo, m_internalVertices, sizeof(m3d::InternalTexturedVertex), 2, 0x10);

        C3D_TexBind(0, &m_texture.getTexture());

        C3D_TexEnv* env = C3D_GetTexEnv(0);
        C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, 0, 0);
        C3D_TexEnvOp(env, C3D_Both, 0, 0, 0);
        C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);

        if (m_repeat) C3D_TexSetWrap(&m_texture.getTexture(), GPU_REPEAT, GPU_REPEAT);

        // Draw the VBO
        C3D_DrawElements(GPU_TRIANGLES, 6, GPU_UNSIGNED_BYTE, m_elementData);
    }
} /* m3d */
