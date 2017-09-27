#include "graphics/drawables/rectangle.hpp"

namespace m3d {
	Rectangle::Rectangle(int t_x, int t_y, int t_width, int t_height, m3d::Color t_color) :
		m_posX(t_x),
		m_posY(t_y),
		m_width(t_width),
		m_height(t_height),
		m_color(t_color) {
			updateVertices();
	}

	void Rectangle::setXPosition(int t_x) {
		m_posX = t_x;
		updateVertices();
	}

	int Rectangle::getXPosition() {
		return m_posX;
	}

	void Rectangle::setYPosition(int t_y) {
		m_posY = t_y;
		updateVertices();
	}

	int Rectangle::getYPosition() {
		return m_posY;
	}

	void Rectangle::setPosition(int t_x, int t_y) {
		m_posX = t_x;
		m_posY = t_y;
		updateVertices();
	}

	void Rectangle::setWidth(int t_width) {
		m_width = t_width;
		updateVertices();
	}

	int Rectangle::getWidth() {
		return m_width;
	}

	void Rectangle::setHeight(int t_height) {
		m_height = t_height;
		updateVertices();
	}

	int Rectangle::getHeight() {
		return m_height;
	}

	m3d::BoundingBox Rectangle::getBoundingBox() {
		return m3d::BoundingBox(m_posX, m_posY, m_width, m_height);
	}

	void Rectangle::setColor(m3d::Color t_color) {
		m_color = t_color;
		updateVertices();
	}

	m3d::Color Rectangle::getColor() {
		return m_color;
	}

	void Rectangle::updateVertices() {
		clearVertices();
		addVertex(m_posX, m_posY, 0.5f, m_color);
		addVertex(m_posX, m_posY + m_height, 0.5f, m_color);
		addVertex(m_posX + m_width, m_posY + m_height, 0.5f, m_color);
		addVertex(m_posX + m_width, m_posY, 0.5f, m_color);
	}
} /* m3d */
