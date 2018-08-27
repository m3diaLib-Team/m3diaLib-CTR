/**
 * @file text.hpp
 * @brief Defines the text class
 */
#pragma once
#include <citro2d.h>
#include <string>
#include "graphics/boundingBox.hpp"
#include "graphics/color.hpp"
#include "graphics/drawable.hpp"
#include "graphics/vertex.hpp"

namespace m3d {
    /**
     * @brief The text class used for rendering text
     * @todo Add support for stereoscopic 3D
     */
    class Text: public m3d::Drawable {
    public:
        /**
         * @brief Initializes the text
         */
        Text(const std::string& t_text = "", m3d::Color t_color = m3d::Color(255, 255, 255));

        /**
         * @brief Sets the string of the text
         * @param t_text The string of the text
         */
        void setText(const std::string& t_text);

        /**
         * @brief Returns the string of the text
         * @return The string of the text
         */
        std::string getText();

        /**
         * @brief Appends a given string to the text
         * @param t_text The string to append
         */
        void appendText(const std::string& t_text);

        /**
         * @brief Sets the x position of the text
         * @param t_y The x position
         */
        void setXPosition(int t_x);

        /**
         * @brief Returns the x position of the text
         * @return The x position
         */
        int getXPosition();

        /**
         * @brief Sets the y position of the text
         * @param t_y The y position
         */
        void setYPosition(int t_y);

        /**
         * @brief Returns the y position of the text
         * @return The y position
         */
        int getYPosition();

        /**
         * @brief Sets the position of the text
         * @param t_x The x position
         * @param t_y The y position
         */
        void setPosition(int t_x, int t_y);

        /**
         * @brief Sets the position of the text
         * @param t_vector The vector representing the position
         * @note The first component of the vector is the x position, the second component is the y position
         */
        void setPosition(m3d::Vector2f t_vector);

        /**
         * @brief Moves the text a certain offset on the x-axis
         * @param t_offset The offset to move
         */
        void moveX(int t_offset);

        /**
         * @brief Moves the text a certain offset on the y-axis
         * @param t_offset The offset to move
         */
        void moveY(int t_offset);

        /**
         * @brief Moves the text a certain offset
         * @param t_offsetX The offset to move on the x-axis
         * @param t_offsetY The offset to move on the y-axis
         */
        void move(int t_offsetX, int t_offsetY);

        /**
         * @brief Moves the text a certain offset
         * @param t_vector The vector to move
         * @note The first component of the vector is the offset to move on the x-axis, the second component is the offset on the y-axis
         */
        void move(Vector2f t_vector);

        /**
         * @brief Returns the width of the text
         * @return The width
         */
        int getWidth();

        /**
         * @brief Returns the height of the text
         * @return The height
         */
        int getHeight();

        /**
         * @brief Returns the current bounding box of the text
         * @return The bounding box
         */
        BoundingBox getBoundingBox();

        /**
         * @brief Sets the text color
         * @param t_color The color of the text
         */
        void setColor(m3d::Color t_color);

        /**
         * @brief Returns the text color
         * @return The color of the text
         */
        m3d::Color getColor();

        /**
         * @brief Sets the opacity of the text
         * @param t_opacity The opacity of the text
         */
        void setOpacity(unsigned int t_opacity);

        /**
         * @brief Returns the opacity of the text
         * @return The opacity of the text
         */
        unsigned int getOpacity();

        /**
         * @brief Sets the font size of the text
         * @param t_size The new font size
         */
        void setFontSize(float t_size);

        /**
         * @brief Returns the current font size of the text
         * @return The font size
         * @note 1.0f corresponds to the native font size
         */
        float getFontSize();

        /**
         * @brief Sets the font weight of the text
         * @param t_weight The new font weight
         * @note 1.0f corresponds to the native font weight
         */
        void setFontWeight(float t_weight);

        /**
         * @brief Returns the current font weight of the text
         * @return The font weight
         * @note 1.0f corresponds to the native font weight
         */
        float getFontWeight();

        /**
         * @brief Sets whether to draw the text on the baseline or not
         * @param t_baseline Whether to draw on the baseline or not
         * @note If this is enabled, the text won't be drawn from the y-position down but will rather use the y-position as it's baseline
         * @note By default, this is false
         */
        void setDrawAtBaseline(bool t_baseline);

        /**
         * @brief Sets whether to draw the text on the baseline or not
         * @return Whether to draw on the baseline or not
         */
        bool getDrawAtBaseline();

        /**
         * @brief Draws the text
         * @param t_3dEnabled Whether stereoscopic 3D is enabled or not
         * @param t_side      The current 3D side (0 = left, 1 = right)
         */
        void draw(bool t_3dEnabled = false, int t_side = 0);

    private:
        /* data */
        int m_posX, m_posY;
        float m_scaleX, m_scaleY;
        bool m_baseline;
        std::string m_text;
        m3d::Color m_color;
        C2D_Text m_textObject;
        C2D_TextBuf m_textBuffer;
    };
} /* m3d */
