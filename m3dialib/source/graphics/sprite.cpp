#include "graphics/drawables/sprite.hpp"

namespace m3d {
    Sprite::Sprite() :
            m_posX(0),
            m_posY(0),
            m_centerX(0),
            m_centerY(0),
            m_opacity(255),
            m_index(0),
            m_scaleX(1.0f),
            m_scaleY(1.0f),
            m_rotation(0.f),
            m_blendStrength(0.f),
            m_spriteSheetPath(""),
            m_tintColor(m3d::Color(255, 255, 255, 255)) {
                updateTint();
                m_spriteSheet = nullptr;
            }

    Sprite::Sprite(const std::string& t_spriteSheet, int t_imageId) :
            m_posX(0),
            m_posY(0),
            m_centerX(0),
            m_centerY(0),
            m_opacity(255),
            m_scaleX(1.0f),
            m_scaleY(1.0f),
            m_rotation(0),
            m_blendStrength(0.f),
            m_tintColor(m3d::Color(255, 255, 255, 255)) {
                updateTint();
                setSpriteSheet(t_spriteSheet, t_imageId);
            }

    void Sprite::setXPosition(int t_x) {
        m_posX = t_x;
        update();
    }

    int Sprite::getXPosition() {
        return m_posX;
    }

    void Sprite::setYPosition(int t_y) {
        m_posY = t_y;
        update();
    }

    int Sprite::getYPosition() {
        return m_posY;
    }

    void Sprite::setPosition(int t_x, int t_y) {
        m_posX = t_x;
        m_posY = t_y;
        update();
    }

    void Sprite::setPosition(Vector2f t_vector) {
        m_posX = static_cast<int>(t_vector.u);
        m_posY = static_cast<int>(t_vector.v);
        update();
    }

    void Sprite::moveX(int t_offset) {
        m_posX += t_offset;
        update();
    }

    void Sprite::moveY(int t_offset) {
        m_posY += t_offset;
        update();
    }

    void Sprite::move(int t_offsetX, int t_offsetY) {
        m_posX += t_offsetX;
        m_posY += t_offsetY;
        update();
    }

    void Sprite::move(Vector2f t_vector) {
        m_posX += static_cast<int>(t_vector.u);
        m_posY += static_cast<int>(t_vector.v);
        update();
    }

    void Sprite::setCenterX(int t_x) {
        m_centerX = t_x;
        update();
    }

    int Sprite::getCenterX() {
        return m_centerX;
    }

    void Sprite::setCenterY(int t_y) {
        m_centerY = t_y;
        update();
    }

    int Sprite::getCenterY() {
        return m_centerY;
    }

    void Sprite::setCenter(int t_x, int t_y) {
        m_centerX = t_x;
        m_centerY = t_y;
        update();
    }

    void Sprite::setCenter(Vector2f t_vector) {
        m_centerX = static_cast<int>(t_vector.u);
        m_centerY = static_cast<int>(t_vector.v);
        update();
    }

    void Sprite::setXScale(float t_scale) {
        m_scaleX = t_scale;
        update();
    }

    float Sprite::getXScale() {
        return m_scaleX;
    }

    void Sprite::setYScale(float t_scale) {
        m_scaleY = t_scale;
        update();
    }

    float Sprite::getYScale() {
        return m_scaleY;
    }

    void Sprite::setScale(float t_yScale, float t_xScale) {
        m_scaleX = t_xScale;
        m_scaleY = t_yScale;
        update();
    }

    void Sprite::scaleX(float t_delta) {
        m_scaleX += t_delta;
        update();
    }

    void Sprite::scaleY(float t_delta) {
        m_scaleY += t_delta;
        update();
    }

    void Sprite::scale(float t_deltaX, float t_deltaY) {
        m_scaleX += t_deltaX;
        m_scaleY += t_deltaY;
        update();
    }

    void Sprite::setRotation(float t_rotation, bool t_radians) {
        m_rotation = t_radians ?
                        t_rotation * (180.0/3.141592653589793238463) :
                        t_rotation;
        update();
    }

    void Sprite::rotate(float t_delta, bool t_radians) {
        m_rotation += t_radians ?
                        t_delta * (180.0/3.141592653589793238463) :
                        t_delta;
        update();
    }

    void Sprite::setTint(m3d::Color t_color) {
        m_tintColor = t_color;
        updateTint();
    }

    m3d::Color Sprite::getTint() {
        return m_tintColor;
    }

    void Sprite::setBlend(float t_blend) {
        if (t_blend < 0.f) m_blendStrength = 0.f;
        else if (t_blend > 1.f) m_blendStrength = 1.f;
        else m_blendStrength = t_blend;

        updateTint();
    }

    float Sprite::getBlend() {
        return m_blendStrength;
    }

    void Sprite::setOpacity(unsigned int t_opacity) {
        m_opacity = t_opacity;
        updateTint();
    }

    float Sprite::getOpacity() {
        return m_opacity;
    }

    void Sprite::setSpriteSheet(const std::string& t_spriteSheet, int t_imageId) {
        m_spriteSheetPath = t_spriteSheet;
        m_index = t_imageId;
        m_spriteSheet = C2D_SpriteSheetLoad(m_spriteSheetPath.c_str());

        update();
    }

    const std::string& Sprite::getSpriteSheet() {
        return m_spriteSheetPath;
    }

    void Sprite::draw(bool t_3dEnabled, int t_side) {
        C2D_DrawSpriteTinted(&m_sprite, &m_imageTint);
    }

    // private methods
    void Sprite::update() {
        C2D_SpriteFromSheet(&m_sprite, m_spriteSheet, m_index);
        C2D_SpriteSetCenterRaw(&m_sprite, m_centerX, m_centerY);
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
        C2D_SpriteSetScale(&m_sprite, m_scaleX, m_scaleY);
        C2D_SpriteSetRotationDegrees(&m_sprite, m_rotation);
    }

    void Sprite::updateTint() {
        C2D_Tint tint = {
            m3d::Color(m_tintColor.getRed(), m_tintColor.getGreen(), m_tintColor.getBlue(), m_opacity).getRgba8(),
            m_blendStrength
        };

        m_imageTint = { tint, tint, tint, tint };
    }
} /* m3d */
