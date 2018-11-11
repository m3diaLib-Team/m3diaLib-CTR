#include <citro3d.h>
#include "m3d/graphics/renderTarget.hpp"
#include "m3d/private/graphics.hpp"

namespace m3d {
    namespace priv {
        namespace graphics {
            int GPU::m_vertexAmount = 0;
            int GPU::m_lastPos = 0;
            Vertex* GPU::m_vertexBuffer = nullptr;
            m3d::RenderContext::Mode GPU::m_mode = m3d::RenderContext::Mode::Flat;

            void GPU::renderTo(const m3d::RenderTarget& t_target) {
                C3D_FrameDrawOn(t_target.getRenderTarget());
            }

            void GPU::addVertex(Vertex t_vertex) {
                if (m_vertexAmount < 4096 * 3) {
                    Vertex* vtx = &m_vertexBuffer[m_vertexAmount++];

                    vtx->pos[0]      = t_vertex.pos[0];
                    vtx->pos[1]      = t_vertex.pos[1];
                    vtx->pos[2]      = t_vertex.pos[2];
                    vtx->texcoord[0] = t_vertex.texcoord[0];
                    vtx->texcoord[1] = t_vertex.texcoord[1];
                    vtx->normals[0]  = t_vertex.normals[0];
                    vtx->normals[1]  = t_vertex.normals[1];
                    vtx->normals[2]  = t_vertex.normals[2];
                    vtx->blend[0]    = t_vertex.blend[0];
                    vtx->blend[1]    = t_vertex.blend[1];
                    vtx->color       = t_vertex.color;
                }
            }

            void GPU::draw() {
                C3D_DrawArrays(GPU_TRIANGLES, m_lastPos, m_vertexAmount - m_lastPos);

                m_lastPos = m_vertexAmount;
            }
        } /* graphics */
    } /* priv */
} /* m3d */
