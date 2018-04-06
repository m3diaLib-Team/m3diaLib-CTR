/**
 * @file circle.hpp
 * @brief Defines the circle shape
 */
#pragma once
#include "graphics/drawables/shape.hpp"
#include "graphics/boundingBox.hpp"

namespace m3d {
    /**
     * @brief The circle shape
     * @todo Implement support for gradients
     */
    class Circle: public m3d::Shape {
    public:
        /**
         * @brief Creates the circle
         * @param t_x      The x position of the circle
         * @param t_y      The y position of the circle
         * @param t_radius The radius of the circle
         * @param t_color  The fill color of the circle
         */
        Circle(int t_x, int t_y, int t_radius, m3d::Color t_color);

        /**
         * @brief Sets the x position of the circle
         * @param t_x The x position
         */
        void setXPosition(int t_x);

        /**
         * @brief Returns the x position of the circle
         * @return The x position
         */
        int getXPosition();

        /**
         * @brief Sets the y position of the circle
         * @param t_y The y position
         */
        void setYPosition(int t_y);

        /**
         * @brief Returns the y position of the circle
         * @return The y position
         */
        int getYPosition();

        /**
         * @brief Sets the x and y position of the circle
         * @param t_x The x position
         * @param t_y The y position
         */
        void setPosition(int t_x, int t_y);

        /**
         * @brief Sets the radius of the circle
         * @param t_radius The radius
         */
        void setRadius(int t_radius);

        /**
         * @brief Returns the radius of the circle
         * @return The radius
         */
        int getRadius();

        /**
         * @brief Returns the bounding box of the circle
         * @return The bounding box
         */
        m3d::BoundingBox getBoundingBox();

        /**
         * @brief Sets the X origin of the circle
         * @param t_radius The X origin
         */
        void setOriginX(int t_originX);

        /**
         * @brief Returns the X origin of the circle
         * @return The X origin
         */
        int getOriginX();

        /**
         * @brief Sets the Y origin of the circle
         * @param t_radius The Y origin
         */
        void setOriginY(int t_originY);

        /**
         * @brief Returns the Y origin of the circle
         * @return The Y origin
         */
        int getOriginY();

        /**
         * @brief Sets the origin of the circle
         * @param t_radius The origin
         */
        void setOrigin(int t_originX, int t_originY);

        /**
         * @brief Returns the origin of the circle
         * @return The origin
         */
        int getOrigin();

        /**
         * @brief Sets the fill color of the circle
         * @param t_color The color
         */
        void setColor(m3d::Color t_color);

        /**
         * @brief Returns the fill color of the circle
         * @return The color
         */
        m3d::Color getColor();

    private:
        /* data */
        int m_posX, m_posY, m_radius, m_originX, m_originY;
        m3d::Color m_color;
        void updateVertices();

    };
} /* m3d */
