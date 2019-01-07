/**
 * @file vertex.hpp
 * @brief Defines the Vertex structs as well as multi-dimensional vectors used for shapes
 */
#ifndef VERTEX_H
#define VERTEX_H

#pragma once
#include "color.hpp"

namespace m3d {
    /**
     * @brief Represents a two dimensional float vector
     */
    struct Vector2f {
        float u;  ///< First component of the vector
        float v;  ///< Second component of the vector
    };

    /**
     * @brief Represents a three dimensional float vector
     */
    struct Vector3f {
        float x;  ///< First component of the vector
        float y;  ///< Second component of the vector
        float z;  ///< Third component of the vector
    };

    /**
     * @brief Represents a vertex which can be sent to the GPU
     */
    struct Vertex {
        float pos[3];      ///< The position
        float texcoord[2]; ///< The texture coordinates
        float normals[3];  ///< The normal vectors
        float blend[2];    ///< The blend
        u32 color;         ///< The color
    };

    /**
     * @brief Represents a vertex containing its position and its color
     */
    struct ColoredVertex {
        Vector3f position;  ///< Position of the vertex
        m3d::Color color;   ///< Color of the vertex
    };

    /**
     * @brief Represents a vertex containing its position and its texture coordinates
     */
    struct TexturedVertex {
        Vector3f position;       ///< Position of the vertex
        Vector2f textureCoords;  ///< Texture coordinates of the vertex
    };
} /* m3d */

#endif /* end of include guard: VERTEX_H */
