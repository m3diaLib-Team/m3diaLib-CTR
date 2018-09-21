#include "m3d/graphics/drawables/meshes/cuboid.hpp"

namespace m3d {
    Cuboid::Cuboid(float t_length, float t_width, float t_height) {
        m_length = t_length;
        m_width = t_width;
        m_height = t_height;
        update();
    }

    void Cuboid::setLength(float t_length) {
        m_length = t_length;
    }

    float Cuboid::getLength() {
        return m_length;
    }

    void Cuboid::setWidth(float t_width) {
        m_width = t_width;
    }

    float Cuboid::getWidth() {
        return m_width;
    }

    void Cuboid::setHeight(float t_height) {
        m_height = t_height;
    }

    float Cuboid::getHeight() {
        return m_height;
    }

    // private methods
    void Cuboid::update() {
        clearVertices();

        // first face (PZ)
        addPolygon(m3d::Mesh::Polygon(
            { {-(m_width / 2), -(m_height / 2), (m_length / 2)}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
            { {(m_width / 2), -(m_height / 2), (m_length / 2)}, {1.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
            { {(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {0.0f, 0.0f, +1.0f} }
        ));

        addPolygon(m3d::Mesh::Polygon(
            { {(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {0.0f, 0.0f, +1.0f} },
            { {-(m_width / 2), (m_height / 2), (m_length / 2)}, {0.0f, 1.0f}, {0.0f, 0.0f, +1.0f} },
            { {-(m_width / 2), -(m_height / 2), (m_length / 2)}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} }
        ));

        // second face (MZ)
        addPolygon(m3d::Mesh::Polygon(
            { {-(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f} },
            { {-(m_width / 2), (m_height / 2), -(m_length / 2)}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f} },
            { {(m_width / 2), (m_height / 2), -(m_length / 2)}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} }
        ));

        addPolygon(m3d::Mesh::Polygon(
            { {(m_width / 2), (m_height / 2), -(m_length / 2)}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} },
            { {(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f} },
            { {-(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f} }
        ));

        // third face (PX)
        addPolygon(m3d::Mesh::Polygon(
            { {(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {+1.0f, 0.0f, 0.0f} },
            { {(m_width / 2), (m_height / 2), -(m_length / 2)}, {1.0f, 0.0f}, {+1.0f, 0.0f, 0.0f} },
            { {(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {+1.0f, 0.0f, 0.0f} }
        ));

        addPolygon(m3d::Mesh::Polygon(
            { {(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {+1.0f, 0.0f, 0.0f} },
            { {(m_width / 2), -(m_height / 2), (m_length / 2)}, {0.0f, 1.0f}, {+1.0f, 0.0f, 0.0f} },
            { {(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {+1.0f, 0.0f, 0.0f} }
        ));

        // fourth face (MX)
        addPolygon(m3d::Mesh::Polygon(
            { {-(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f} },
            { {-(m_width / 2), -(m_height / 2), (m_length / 2)}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f} },
            { {-(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} }
        ));

        addPolygon(m3d::Mesh::Polygon(
            { {-(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} },
            { {-(m_width / 2), (m_height / 2), -(m_length / 2)}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} },
            { {-(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f} }
        ));

        // fifth face (PY)
        addPolygon(m3d::Mesh::Polygon(
            { {-(m_width / 2), (m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {0.0f, +1.0f, 0.0f} },
            { {-(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 0.0f}, {0.0f, +1.0f, 0.0f} },
            { {(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {0.0f, +1.0f, 0.0f} }
        ));

        addPolygon(m3d::Mesh::Polygon(
            { {(m_width / 2), (m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {0.0f, +1.0f, 0.0f} },
            { {(m_width / 2), (m_height / 2), -(m_length / 2)}, {0.0f, 1.0f}, {0.0f, +1.0f, 0.0f} },
            { {-(m_width / 2), (m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {0.0f, +1.0f, 0.0f} }
        ));

        // sixth face (MY)
        addPolygon(m3d::Mesh::Polygon(
            { {-(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f} },
            { {(m_width / 2), -(m_height / 2), -(m_length / 2)}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f} },
            { {(m_width / 2), -(m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} }
        ));

        addPolygon(m3d::Mesh::Polygon(
            { {(m_width / 2), -(m_height / 2), (m_length / 2)}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} },
            { {-(m_width / 2), -(m_height / 2), (m_length / 2)}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f} },
            { {-(m_width / 2), -(m_height / 2), -(m_length / 2)}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f} }
        ));
    }
} /* m3d */
