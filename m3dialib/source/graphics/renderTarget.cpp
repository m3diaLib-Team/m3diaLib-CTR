#include "m3d/graphics/renderTarget.hpp"
#include "m3d/graphics/color.hpp"

namespace m3d {
    RenderTarget::RenderTarget(int t_width, int t_height) :
        m_width(t_width),
        m_height(t_height),
        m_clearColor(RGBA8(0, 0, 0, 255)) {
            m_target = C3D_RenderTargetCreate(t_height, t_width, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
    }

    C3D_RenderTarget* RenderTarget::getRenderTarget() {
        return m_target;
    }

    int RenderTarget::getWidth() {
        return m_width;
    }

    int RenderTarget::getHeight() {
        return m_height;
    }

    void RenderTarget::setClearColor(u32 t_color) {
        m_clearColor = t_color;
    }

    void RenderTarget::clear() {
        C2D_TargetClear(m_target, m_clearColor);
    }

    u32 RenderTarget::getClearColor() {
        return m_clearColor;
    }
} /* m3d */
