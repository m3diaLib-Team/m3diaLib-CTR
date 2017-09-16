/**
 * @file shape.hpp
 * @brief Defines the base class for all shapes
 */
#pragma once
#include <vector>
#include "graphics/drawable.hpp"
#include "graphics/color.hpp"
#include "graphics/vertex.hpp"

namespace m3d {
	/**
	 * @brief The base class for all shapes
	 * @todo Add support for direct editing of the vertices
	 * @todo Add support for stereoscopic 3D
	 * @todo Implement support for textures
	 */
	class Shape: public m3d::Drawable {
	public:
		/**
		 * @brief Initializes the shape
		 */
		Shape();

		/**
		 * @brief Destructs the shape
		 */
		virtual ~Shape();

		/**
		 * @brief Adds a vertex by a m3d::Vertex struct
		 * @param t_vertex The vertex to add
		 */
		void addVertex(m3d::Vertex t_vertex);

		/**
		 * @brief Adds a vertex given it's position and color
		 * @param t_x     The x position
		 * @param t_y     The y position
		 * @param t_z     The z position
		 * @param t_color The color
		 * @note Typically, you want to set t_z to 0.5f
		 */
		void addVertex(int t_x, int t_y, int t_z, m3d::Color t_color);

		/**
		 * @brief Removes all vertices
		 */
		void clearVertices();

		/**
		 * @brief Draws the shape
		 * @param t_side The current 3D side (0 = left, 1 = right)
		 * @param t_projection The projection uniform of the shader
		 * @param t_transform The transform uniform of the shader
		 * @param t_useTransform The useTransform uniform of the shader
		 */
		void draw(int t_side, int t_projection, int t_transform, int t_useTransform);

	private:
		/* data */
		bool m_changed;
		std::vector<m3d::Vertex> m_vertices;
		m3d::InternalVertex* m_internalVertices;
	};
} /* m3d */
