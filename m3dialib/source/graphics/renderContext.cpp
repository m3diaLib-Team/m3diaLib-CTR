#include "m3d/graphics/renderContext.hpp"

namespace m3d {
    RenderContext::RenderContext(
        int t_projectionUniform,
        int t_modelViewUniform,
        int t_lightVecUniform,
        int t_lightHalfVecUniform,
        int t_lightColorUniform,
        int t_materialUniform,
        bool t_3dEnabled,
        m3d::RenderContext::Mode t_mode,
        m3d::RenderContext::Stereo3dSide t_side,
        m3d::RenderContext::ScreenTarget t_target,
        C3D_Mtx& t_projection,
        C3D_Mtx& t_modelView
    ) :
    m_projectionUniformLocation(t_projectionUniform),
    m_modelViewUniformLocation(t_modelViewUniform),
    m_lightVecUniformLocation(t_lightVecUniform),
    m_lightHalfVecUniformLocation(t_lightHalfVecUniform),
    m_lightColorUniformLocation(t_lightColorUniform),
    m_materialUniformLocation(t_materialUniform),
    m_3dEnabled(t_3dEnabled),
    m_mode(t_mode),
    m_side(t_side),
    m_target(t_target),
    m_projection(t_projection),
    m_modelView(t_modelView) { /* do nothing */ }

    int RenderContext::getProjectionUniform() {
        return m_projectionUniformLocation;
    }

    int RenderContext::getModelViewUniform() {
        return m_modelViewUniformLocation;
    }

    int RenderContext::getLightVecUniform() {
        return m_lightVecUniformLocation;
    }

    int RenderContext::getLightHalfVecUniform() {
        return m_lightHalfVecUniformLocation;
    }

    int RenderContext::getLightColorUniform() {
        return m_lightColorUniformLocation;
    }

    int RenderContext::getMaterialUniform() {
        return m_materialUniformLocation;
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

    m3d::RenderContext::ScreenTarget RenderContext::getScreenTarget() {
        return m_target;
    }

    C3D_Mtx& RenderContext::getProjectionMatrix() {
        return m_projection;
    }

    C3D_Mtx& RenderContext::getModelViewMatrix() {
        return m_modelView;
    }

    void RenderContext::enableTextures(bool t_enable) {
        C3D_TexEnv* env;

        switch (t_enable) {
            case true:
                env = C3D_GetTexEnv(0);
                C3D_TexEnvInit(env);
                C3D_TexEnvSrc(env, C3D_Both, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR, GPU_PRIMARY_COLOR);
                C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_FRAGMENT_SECONDARY_COLOR, GPU_PRIMARY_COLOR);
                C3D_TexEnvFunc(env, C3D_Both, GPU_ADD);
                break;
            default:
                env = C3D_GetTexEnv(0);
                C3D_TexEnvInit(env);
                C3D_TexEnvSrc(env, C3D_Both, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR, GPU_PRIMARY_COLOR);
                C3D_TexEnvFunc(env, C3D_Both, GPU_ADD);
        }
    }
} /* m3d */
