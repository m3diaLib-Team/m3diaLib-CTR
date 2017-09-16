/**
 * @file rectangle.hpp
 * @brief Defines the rectangle shape
 */
#pragma once
#include "graphics/drawables/shape.hpp"
#include "graphics/boundingBox.hpp"

namespace m3d {
	/**
	 * @brief The rectangle shape
	 * @todo Implement support for gradients
	 */
	class Rectangle: public m3d::Shape {
	public:
		/**
		 * @brief Creates the rectangle
		 * @param t_x      The x position of the rectangle
		 * @param t_y      The y position of the rectangle
		 * @param t_width  The width of the rectangle
		 * @param t_height The height of the rectangle
		 * @param t_color  The fill color of the rectangle
		 */
		Rectangle(int t_x, int t_y, int t_width, int t_height, m3d::Color t_color);

		/**
		 * @brief Sets the x position of the rectangle
		 * @param t_x The x position
		 */
		void setXPosition(int t_x);

		/**
		 * @brief Returns the x position of the rectangle
		 * @return The x position
		 */
		int getXPosition();

		/**
		 * @brief Sets the y position of the rectangle
		 * @param t_y The y position
		 */
		void setYPosition(int t_y);

		/**
		 * @brief Returns the y position of the rectangle
		 * @return The y position
		 */
		int getYPosition();

		/**
		 * @brief Sets the x and y position of the rectangle
		 * @param t_x The x position
		 * @param t_y The y position
		 */
		void setPosition(int t_x, int t_y);

		/**
		 * @brief Sets the width of the rectangle
		 * @param t_width The width
		 */
		void setWidth(int t_width);

		/**
		 * @brief Returns the width of the rectangle
		 * @return The width
		 */
		int getWidth();

		/**
		 * @brief Sets the height of the rectangle
		 * @param t_height The height
		 */
		void setHeight(int t_height);

		/**
		 * @brief Returns the height of the rectangle
		 * @return The height
		 */
		int getHeight();

		/**
		 * @brief Returns the bounding box of the rectangle
		 * @return The bounding box
		 */
		m3d::BoundingBox getBoundingBox();

		/**
		 * @brief Sets the fill color of the rectangle
		 * @param t_color The color
		 */
		void setColor(m3d::Color t_color);

		/**
		 * @brief Returns the fill color of the rectangle
		 * @return The color
		 */
		m3d::Color getColor();

	private:
		/* data */
		int m_posX, m_posY, m_width, m_height;
		m3d::Color m_color;
		m3d::InternalVertex* m_vertices;
		void updateVertices();

	};
} /* m3d */
