/**
 * @file cuboid.hpp
 * @brief Defines the cuboid mesh
 */
#ifndef CUBOID_H
#define CUBOID_H

#pragma once
#include "m3d/graphics/drawables/mesh.hpp"

namespace m3d {
    /**
     * @brief The cuboid mesh
     */
    class Cuboid: public m3d::Mesh {
    public:
        /**
         * @brief Creates the cuboid
         * @param t_length The length of the cuboid
         * @param t_width  The width of the cuboid
         * @param t_height The height of the cuboid
         */
        Cuboid(float t_length, float t_width, float t_height);

        /**
         * @brief Sets the length of the cuboid
         * @param t_length The length
         */
        void setLength(float t_length);

        /**
         * @brief Returns the length of the cuboid
         * @return The length
         */
        float getLength();

        /**
         * @brief Sets the width of the cuboid
         * @param t_width The width
         */
        void setWidth(float t_width);

        /**
         * @brief Returns the width of the cuboid
         * @return The width
         */
        float getWidth();

        /**
         * @brief Sets the height of the cuboid
         * @param t_height The height
         */
        void setHeight(float t_height);

        /**
         * @brief Returns the height of the cuboid
         * @return The height
         */
        float getHeight();

    private:
        void update();

        /* data */
        float m_length, m_width, m_height;
    };
} /* m3d */


#endif /* end of include guard: CUBOID_H */
