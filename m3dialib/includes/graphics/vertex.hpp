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
	typedef struct {
		float u;  ///< First component of the vector
		float v;  ///< Second component of the vector
	} Vector2f;

	/**
	 * @brief Represents a three dimensional float vector
	 */
	typedef struct {
		float x;  ///< First component of the vector
		float y;  ///< Second component of the vector
		float z;  ///< Third component of the vector
	} Vector3f;

	/**
	 * @brief Represents a vertex containing its position and its color
	 * @todo Refactor this into a class
	 */
	typedef struct {
		Vector3f position;  ///< Position of the vertex
		m3d::Color color;		///< Color of the vertex
	} Vertex;

	/**
	 * @brief Represents a vertex containing it's position and color as arrays
	 * @deprecated Do not use this, it's only for internal use and will soon be removed completely
	 * @todo Get rid of this
	 */
	typedef struct {
		float position[3];
		float color[4];
	} InternalVertex;
} /* m3d */
