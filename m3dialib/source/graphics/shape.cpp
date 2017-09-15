#include "graphics/drawables/shape.hpp"
#include <stdio.h>
namespace m3d {
	Shape::Shape() :
	 				m_changed(true) { /* do nothing */ }

	Shape::~Shape() {
		linearFree(m_internalVertices);
	}

	void Shape::addVertex(m3d::Vertex t_vertex) {
		m_vertices.push_back(t_vertex);
		m_changed = true;
	}

	void Shape::addVertex(int t_x, int t_y, int t_z, m3d::Color t_color) {
		m3d::Vertex vertex = { { (float) t_x, (float) t_y, (float) t_z }, t_color };
		m_vertices.push_back(vertex);
		m_changed = true;
	}

	void Shape::clearVertices() {
		m_vertices.clear();
		linearFree(m_internalVertices);
		m_changed = true;
	}

	void Shape::draw(int t_side) {
		if(m_changed) {
			m_changed = false;
			linearFree(m_internalVertices);
			m_internalVertices = static_cast<m3d::InternalVertex*>(linearAlloc(m_vertices.size() * sizeof(m3d::InternalVertex)));

			if(m_internalVertices == nullptr) return;

			for(unsigned int i = 0; i < m_vertices.size(); i++) {
				float x = m_vertices[i].position.x,
							y = m_vertices[i].position.y,
							red = (float) m_vertices[i].color.getRed() / 255,
							blue = (float) m_vertices[i].color.getBlue() / 255,
							green = (float) m_vertices[i].color.getGreen() / 255,
							alpha = (float) m_vertices[i].color.getAlpha() / 255;

				m_internalVertices[i] = (m3d::InternalVertex) { {x, y, 0.5f}, {red, blue, green, alpha} };
			}
		}

		if(m_internalVertices == nullptr) return;

		C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
		AttrInfo_Init(attrInfo);
		AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // position
		AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 4); // color

		C3D_BufInfo* bufInfo = C3D_GetBufInfo();
		BufInfo_Init(bufInfo);
		BufInfo_Add(bufInfo, m_internalVertices, sizeof(m3d::InternalVertex), 2, 0x10);

		C3D_TexEnv* env = C3D_GetTexEnv(0);
		C3D_TexEnvSrc(env, C3D_Both, GPU_PRIMARY_COLOR, 0, 0);
		C3D_TexEnvOp(env, C3D_Both, 0, 0, 0);
		C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);

		// Draw the VBO
		C3D_DrawArrays(GPU_TRIANGLE_FAN, 0, 4);
	}
} /* m3d */
