/**
 * @file shape.hpp
 * @brief Defines the base class for all shapes
 */
#ifndef SHAPE_H
#define SHAPE_H

#pragma once
#include <vector>
#include "m3d/graphics/drawable.hpp"
#include "m3d/graphics/color.hpp"
#include "m3d/graphics/vertex.hpp"

namespace m3d {
    /**
     * @brief The base class for all shapes
     * @todo Add support for stereoscopic 3D
     * @todo Implement support for textures
     * @todo Add support for holes
     */
    class Shape: public m3d::Drawable {
    public:
        /**
         * @brief Initializes the shape
         */
        Shape();

        /**
         * @brief Adds a vertex given it's position and color
         * @param t_x     The x position
         * @param t_y     The y position
         * @param t_color The color
         */
        void addVertex(int t_x, int t_y, m3d::Color t_color);

        /**
         * @brief Adds a vertex given it's position and color
         * @param t_vertex The position, represented as a 2-dimensional vector
         * @param t_color  The color
         */
        void addVertex(m3d::Vector2f t_vertex, m3d::Color t_color);

        /**
         * @brief Removes all vertices
         */
        void clearVertices();

        /**
         * @brief Draws the shape
         * @param t_context the RenderContext
         */
        void draw(m3d::RenderContext t_context);

    private:
        /* data */
        bool m_changed;
        std::vector<std::pair<m3d::Vector2f, m3d::Color>> m_vertices;
        std::vector<uint16_t> m_indices;
    };
} /* m3d */


#endif /* end of include guard: SHAPE_H */
