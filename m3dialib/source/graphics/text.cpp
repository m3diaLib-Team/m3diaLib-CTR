#include "m3d/graphics/drawables/text.hpp"

namespace m3d {
    Text::Text(const std::string& t_text, m3d::Color t_color) :
        m_posX(0),
        m_posY(0),
        m_scaleX(1.f),
        m_scaleY(1.f),
        m_baseline(false),
        m_text(t_text),
        m_color(t_color) {
            m_textBuffer = C2D_TextBufNew(4096);
            C2D_TextParse(&m_textObject, m_textBuffer, m_text.c_str());
            C2D_TextOptimize(&m_textObject);
        }

    void Text::setText(const std::string& t_text) {
        m_text = t_text;
        C2D_TextParse(&m_textObject, m_textBuffer, m_text.c_str());
        C2D_TextOptimize(&m_textObject);
    }

    std::string Text::getText() {
        return m_text;
    }

    void Text::appendText(const std::string& t_text) {
        m_text += t_text;
        C2D_TextParse(&m_textObject, m_textBuffer, m_text.c_str());
        C2D_TextOptimize(&m_textObject);
    }

    void Text::setXPosition(int t_x) {
        m_posX = t_x;
    }

    int Text::getXPosition() {
        return m_posX;
    }

    void Text::setYPosition(int t_y) {
        m_posY = t_y;
    }

    int Text::getYPosition() {
        return m_posY;
    }

    void Text::setPosition(int t_x, int t_y) {
        m_posX = t_x;
        m_posY = t_y;
    }

    void Text::setPosition(m3d::Vector2f t_vector) {
        m_posX = t_vector.u;
        m_posY = t_vector.v;
    }

    void Text::moveX(int t_offset) {
        m_posX += t_offset;
    }

    void Text::moveY(int t_offset) {
        m_posY += t_offset;
    }

    void Text::move(int t_offsetX, int t_offsetY) {
        m_posX += t_offsetX;
        m_posY += t_offsetY;
    }

    void Text::move(Vector2f t_vector) {
        m_posX += static_cast<int>(t_vector.u);
        m_posY += static_cast<int>(t_vector.v);
    }

    int Text::getWidth() {
        float width;
        C2D_TextGetDimensions(&m_textObject, m_scaleX, m_scaleY, &width, nullptr);
        return width;
    }

    int Text::getHeight() {
        float height;
        C2D_TextGetDimensions(&m_textObject, m_scaleX, m_scaleY, nullptr, &height);
        return height;
    }

    BoundingBox Text::getBoundingBox() {
        float width, height;
        C2D_TextGetDimensions(&m_textObject, m_scaleX, m_scaleY, &width, &height);
        return m3d::BoundingBox(m_posX, m_posY, static_cast<int>(width), static_cast<int>(height));
    }

    void Text::setColor(m3d::Color t_color) {
        m_color = t_color;
    }

    m3d::Color Text::getColor() {
        return m_color;
    }

    void Text::setOpacity(unsigned int t_opacity) {
        m_color.setAlpha(t_opacity);
    }

    unsigned int Text::getOpacity() {
        return m_color.getAlpha();
    }

    void Text::setFontSize(float t_size) {
        m_scaleY = t_size;
    }

    float Text::getFontSize() {
        return m_scaleY;
    }

    void Text::setFontWeight(float t_weight) {
        m_scaleX = t_weight;
    }

    float Text::getFontWeight() {
        return m_scaleX;
    }

    void Text::setDrawAtBaseline(bool t_baseline) {
        m_baseline = t_baseline;
    }

    bool Text::getDrawAtBaseline() {
        return m_baseline;
    }

    void Text::draw(m3d::RenderContext t_context) {
        C2D_DrawText(
                    &m_textObject,
                    (m_baseline ? C2D_AtBaseline | C2D_WithColor : C2D_WithColor),
                    static_cast<float>(m_posX),     // x position
                    static_cast<float>(m_posY),     // y position
                    0.5f,                           // z position
                    m_scaleX,                       // x scale
                    m_scaleY,                       // y scale
                    m_color.getRgba8()              // color
                );
    }
} /* m3d */
