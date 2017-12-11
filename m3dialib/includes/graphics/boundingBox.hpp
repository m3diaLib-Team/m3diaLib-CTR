/**
 * @file boundingBox.hpp
 * @brief Defines the BoundingBox class
 */
#pragma once

namespace m3d {
    /**
     * @brief The BoundingBox class
     */
    class BoundingBox {
    public:
        /**
         * @brief Initializes the bounding box
         * @param t_x      The x position
         * @param t_y      The y position
         * @param t_width  The width
         * @param t_height The height
         */
        BoundingBox(int t_x, int t_y, int t_width, int t_height);

        /**
         * @brief Returns the x position of the bounding box
         * @return The x position
         */
        int getX();

        /**
         * @brief Returns the y position of the bounding box
         * @return The y position
         */
        int getY();

        /**
         * @brief Returns the width of the bounding box
         * @return The width
         */
        int getWidth();

        /**
         * @brief Returns the height of the bounding box
         * @return The height
         */
        int getHeight();

    private:
        /* data */
        int m_posX, m_posY, m_width, m_height;

    };
} /* m3d */
