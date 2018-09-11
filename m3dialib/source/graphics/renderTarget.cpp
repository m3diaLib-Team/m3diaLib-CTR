#include <citro2d.h>
#include "m3d/graphics/renderTarget.hpp"
#include "m3d/graphics/color.hpp"

namespace m3d {
    RenderTarget::RenderTarget(int t_width, int t_height) :
        m_width(t_width),
        m_height(t_height),
        m_clearColor(RGBA8(0, 0, 0, 255)) {
            m_target = C3D_RenderTargetCreate(t_height, t_width, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
            Mtx_OrthoTilt(&m_projection, 0.0f, t_width, t_height, 0.0f, 0.0f, 1.0f, true);

            u32 color = ((m_clearColor>>24)&0x000000FF) | ((m_clearColor>>8)&0x0000FF00) | ((m_clearColor<<8)&0x00FF0000) | ((m_clearColor<<24)&0xFF000000); // reverse byte order
            C3D_RenderTargetSetClear(m_target, C3D_CLEAR_ALL, color, 0);
    }

    RenderTarget::RenderTarget(int t_width, int t_height, gfxScreen_t t_screen, gfx3dSide_t t_side = GFX_LEFT) :
        m_width(t_width),
        m_height(t_height),
        m_clearColor(RGBA8(0, 0, 0, 255)) {
            m_target = C2D_CreateScreenTarget(t_screen, t_side);
    }

    C3D_RenderTarget* RenderTarget::getRenderTarget() {
        return m_target;
    }

    C3D_Mtx* RenderTarget::getProjectionMatrix() {
        return &m_projection;
    }

    int RenderTarget::getWidth() {
        return m_width;
    }

    int RenderTarget::getHeight() {
        return m_height;
    }

    void RenderTarget::setClearColor(u32 t_color) {
        m_clearColor = t_color;
        u32 color = ((t_color>>24)&0x000000FF) | ((t_color>>8)&0x0000FF00) | ((t_color<<8)&0x00FF0000) | ((t_color<<24)&0xFF000000); // reverse byte order
        C3D_RenderTargetSetClear(m_target, C3D_CLEAR_ALL, color, 0);
    }

    u32 RenderTarget::getClearColor() {
        return m_clearColor;
    }
} /* m3d */
