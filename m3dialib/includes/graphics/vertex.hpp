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

    /**
     * @brief Represents a vertex containing it's position and color as arrays
     * @deprecated Do not use this, it's only for internal use and will soon be removed completely
     * @todo Get rid of this
     */
    struct InternalColoredVertex {
        float position[3];    ///< The x, y and z position, represented as an array of floats
        float color[4];       ///< The red, green, blue and alpha values, represented as an array of floats
    };

    /**
     * @brief Represents a vertex containing it's position and texture coordinates as arrays
     * @deprecated Do not use this, it's only for internal use and will soon be removed completely
     * @todo Get rid of this
     */
    struct InternalTexturedVertex {
        float position[3];    ///< The x, y and z position, represented as an array of floats
        float color[2];       ///< The red, green, blue and alpha values, represented as an array of floats
    };
} /* m3d */
