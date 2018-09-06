#include "m3d/graphics/boundingBox.hpp"

namespace m3d {
    BoundingBox::BoundingBox(int t_x, int t_y, int t_width, int t_height) :
        m_posX(t_x),
        m_posY(t_y),
        m_width(t_width),
        m_height(t_height) { /* do nothing */    }

    int BoundingBox::getX() {
        return m_posX;
    }

    int BoundingBox::getY() {
        return m_posY;
    }

    int BoundingBox::getWidth() {
        return m_width;
    }

    int BoundingBox::getHeight() {
        return m_height;
    }

    bool BoundingBox::intersects(m3d::BoundingBox t_box) {
        if (m_posX < (t_box.getX() + t_box.getWidth())
            && (m_posX + m_width) > t_box.getX()
            && m_posY < (t_box.getY() + t_box.getHeight())
            && (m_posY + m_height) > t_box.getY()) {
                return true;
            }

        return false;
    }
} /* m3d */
