#include "graphics/drawables/triangle.hpp"

namespace m3d {
	Triangle::Triangle(int t_x1, int t_y1, int t_x2, int t_y2, int t_x3, int t_y3, m3d::Color t_color) :
	 	m_posX1(t_x1),
		m_posY1(t_y1),
		m_posX2(t_x2),
		m_posY2(t_y2),
		m_posX3(t_x3),
		m_posY3(t_y3),
		m_color(t_color) {
			updateVertices();
	}

	void Triangle::setX1Pos(int t_pos) {
		m_posX1 = t_pos;
		updateVertices();
	}

	int Triangle::getX1Pos() {
		return m_posX1;
	}

	void Triangle::setY1Pos(int t_pos) {
		m_posY1 = t_pos;
		updateVertices();
	}

	int Triangle::getY1Pos() {
		return m_posY1;
	}

	void Triangle::setX2Pos(int t_pos) {
		m_posX2 = t_pos;
		updateVertices();
	}

	int Triangle::getX2Pos() {
		return m_posX2;
	}

	void Triangle::setY2Pos(int t_pos) {
		m_posY2 = t_pos;
		updateVertices();
	}

	int Triangle::getY2Pos() {
		return m_posY2;
	}

	void Triangle::setX3Pos(int t_pos) {
		m_posX3 = t_pos;
		updateVertices();
	}

	int Triangle::getX3Pos() {
		return m_posX3;
	}

	void Triangle::setY3Pos(int t_pos) {
		m_posY3 = t_pos;
		updateVertices();
	}

	int Triangle::getY3Pos() {
		return m_posY3;
	}

	void Triangle::setColor(m3d::Color t_color) {
		m_color = t_color;
		updateVertices();
	}

	m3d::Color Triangle::getColor() {
		return m_color;
	}

	void Triangle::updateVertices() {
		addVertex(m_posX1, m_posY1, 0.5f, m_color);
		addVertex(m_posX2, m_posY2, 0.5f, m_color);
		addVertex(m_posX3, m_posY3, 0.5f, m_color);
	}
} /* m3d */
