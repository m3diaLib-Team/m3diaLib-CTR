#include "m3d/graphics/drawables/circle.hpp"
#include <math.h>

namespace m3d {
    Circle::Circle(int t_x, int t_y, int t_radius, m3d::Color t_color) :
        m_posX(t_x),
        m_posY(t_y),
        m_radius(t_radius),
        m_originX(0),
        m_originY(0),
        m_color(t_color) {
            updateVertices();
    }

    void Circle::setXPosition(int t_x) {
        m_posX = t_x;
        updateVertices();
    }

    int Circle::getXPosition() {
        return m_posX;
    }

    void Circle::setYPosition(int t_y) {
        m_posY = t_y;
        updateVertices();
    }

    int Circle::getYPosition() {
        return m_posY;
    }

    void Circle::setPosition(int t_x, int t_y) {
        m_posX = t_x;
        m_posY = t_y;
        updateVertices();
    }

    void Circle::setRadius(int t_radius) {
        m_radius = t_radius;
        updateVertices();
    }

    int Circle::getRadius() {
        return m_radius;
    }

    m3d::BoundingBox Circle::getBoundingBox() {
        return m3d::BoundingBox(m_posX, m_posY, m_posX + m_radius, m_posY + m_radius);
    }

    void Circle::setOriginX(int t_originX) {
        m_originX = t_originX;
        updateVertices();
    }

    int Circle::getOriginX() {
        return m_originX;
    }

    void Circle::setOriginY(int t_originY) {
        m_originY = t_originY;
        updateVertices();
    }

    int Circle::getOriginY() {
        return m_originY;
    }

    void Circle::setOrigin(int t_originX, int t_originY) {
        m_originX = t_originX;
        m_originY = t_originY;
        updateVertices();
    }

    void Circle::setColor(m3d::Color t_color) {
        m_color = t_color;
        updateVertices();
    }

    m3d::Color Circle::getColor() {
        return m_color;
    }

    // private methods
    void Circle::updateVertices() {
        clearVertices();

        static const int num_segments = 100;
        float xx = m_radius;
        float yy = 0;

        float theta = 2 * M_PI / (float) num_segments;
        float c = cosf(theta);
        float s = sinf(theta);
        float t;

        for (int i = 1; i <= num_segments; i++) {
            addVertex((float) (m_posX + xx + m_radius - m_originX), (float) (m_posY + yy + m_radius - m_originY), m_color);

            t = xx;
            xx = c * xx - s * yy;
            yy = s * t + c * yy;
        }
    }
} /* m3d */
