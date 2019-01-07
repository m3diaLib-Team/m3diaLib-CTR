#include "m3d/graphics/renderContext.hpp"
#include "m3d/private/graphics.hpp"

namespace m3d {
    bool RenderContext::m_texturesEnabled = false;

    RenderContext::RenderContext(
        int t_modelUniform,
        bool t_3dEnabled,
        m3d::RenderContext::Mode t_mode,
        m3d::RenderContext::Stereo3dSide t_side,
        m3d::RenderContext::RenderTarget t_target,
        C3D_Mtx& t_model,
        C3D_LightEnv& t_lightEnv,
        C3D_Light& t_light,
        C3D_LightLut& t_lightLut
    ) :
    m_modelUniformLocation(t_modelUniform),
    m_3dEnabled(t_3dEnabled),
    m_mode(t_mode),
    m_side(t_side),
    m_target(t_target),
    m_model(t_model),
    m_lightEnv(t_lightEnv),
    m_light(t_light),
    m_lightLut(t_lightLut) { /* do nothing */ }

    int RenderContext::getModelUniform() {
        return m_modelUniformLocation;
    }

    bool RenderContext::is3dEnabled() {
        return m_3dEnabled;
    }

    m3d::RenderContext::Mode RenderContext::getMode() {
        return m_mode;
    }

    m3d::RenderContext::Stereo3dSide RenderContext::getSide() {
        return m_side;
    }

    m3d::RenderContext::RenderTarget RenderContext::getRenderTarget() {
        return m_target;
    }

    C3D_Mtx& RenderContext::getModelMatrix() {
        return m_model;
    }

    C3D_LightEnv& RenderContext::getLightEnvironment() {
        return m_lightEnv;
    }

    C3D_Light& RenderContext::getLight() {
        return m_light;
    }

    C3D_LightLut& RenderContext::getLightLut() {
        return m_lightLut;
    }
} /* m3d */
