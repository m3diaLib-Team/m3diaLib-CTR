/**
 * @file vertex.hpp
 * @brief Defines the Vertex structs as well as multi-dimensional vectors used for shapes
 */
#pragma once
#include "./color.hpp"

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
