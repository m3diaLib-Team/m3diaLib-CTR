#include <citro2d.h>
#include "m3d/graphics/renderTarget.hpp"
#include "m3d/graphics/color.hpp"

namespace m3d {
    RenderTarget::RenderTarget(int t_width, int t_height, m3d::RenderContext::ScreenTarget t_screen, m3d::RenderContext::Stereo3dSide t_side) :
        m_width(t_width),
        m_height(t_height),
        m_clearColor(RGBA8(0, 0, 0, 255)) {
            m_target = C2D_CreateScreenTarget((t_screen == m3d::RenderContext::ScreenTarget::Top ? GFX_TOP : GFX_BOTTOM), (t_side == m3d::RenderContext::Stereo3dSide::Left ? GFX_LEFT : GFX_RIGHT));
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
