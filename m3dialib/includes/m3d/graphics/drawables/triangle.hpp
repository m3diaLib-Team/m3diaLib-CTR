/**
 * @file triangle.hpp
 * @brief Defines the triangle shape
 */
#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once
#include "shape.hpp"

namespace m3d {
    /**
     * @brief The triangle shape
     * @todo Add support for direct generation of the triangle given only it's coordinates and side-length
     * @todo Implement function to set multiple vertices at once
     */
    class Triangle: public Shape {
    public:
        /**
         * @brief Creates the triangle given the coordinates of it's three vertices
         * @param t_x1 The x position of the topmost corner
         * @param t_y1 The y position of the topmost corner
         * @param t_x2 The x position of the bottom left corner
         * @param t_y2 The y position of the bottom left corner
         * @param t_x3 The x position of the bottom right corner
         * @param t_y3 The y position of the bottom right corner
         * @param t_color The fill color of the rectangle
         */
        Triangle(int t_x1, int t_y1, int t_x2, int t_y2, int t_x3, int t_y3, m3d::Color t_color);

        /**
         * @brief Sets the x position of the topmost corner
         * @param t_pos The position
         */
        void setX1Pos(int t_pos);

        /**
         * @brief Returns the x position of the topmost corner
         * @return The position
         */
        int getX1Pos();

        /**
         * @brief Sets the x position of the topmost corner
         * @param t_pos The position
         */
        void setY1Pos(int t_pos);

        /**
         * @brief Returns the x position of the topmost corner
         * @return The position
         */
        int getY1Pos();

        /**
         * @brief Sets the x position of the bottom left corner
         * @param t_pos The position
         */
        void setX2Pos(int t_pos);

        /**
         * @brief Returns the x position of the bottom left corner
         * @return The position
         */
        int getX2Pos();

        /**
         * @brief Sets the x position of the bottom left corner
         * @param t_pos The position
         */
        void setY2Pos(int t_pos);

        /**
         * @brief Returns the x position of the bottom left corner
         * @return The position
         */
        int getY2Pos();

        /**
         * @brief Sets the x position of the bottom right corner
         * @param t_pos The position
         */
        void setX3Pos(int t_pos);

        /**
         * @brief Returns the x position of the bottom right corner
         * @return The position
         */
        int getX3Pos();

        /**
         * @brief Sets the x position of the bottom right corner
         * @param t_pos The position
         */
        void setY3Pos(int t_pos);

        /**
         * @brief Returns the x position of the bottom right corner
         * @return The position
         */
        int getY3Pos();

        /**
         * @brief Sets the fill color of the triangle
         * @param t_color The color
         */
        void setColor(m3d::Color t_color);

        /**
         * @brief Returns teh fill color of the triangle
         * @return The color
         */
        m3d::Color getColor();
    private:
        void updateVertices();

        /* data */
        int m_posX1, m_posY1, m_posX2, m_posY2, m_posX3, m_posY3;
        m3d::Color m_color;
    };
} /* m3d */

#endif /* end of include guard: TRIANGLE_H */
