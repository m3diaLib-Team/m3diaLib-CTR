#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#pragma once
#include <citro3d.h>

namespace m3d {
    class RenderContext {
    public:
        /**
         * @brief Defines the screen targets (top/bottom)
         */
        enum class ScreenTarget {
            Top,     ///< Top screen
            Bottom   ///< Bottom/touch screen
        };

        /**
         * @brief Defines the two sides in stereoscopic 3D mode
         */
        enum class Stereo3dSide {
            Left, ///< Left side
            Right ///< Right side
        };

        /**
         * @brief Defines the two drawing-modes
         */
        enum class Mode {
            Flat,   ///< 2D
            Spatial ///< 3D
        };

        RenderContext(
            int t_projectionUniform,
            int t_modelViewUniform,
            bool t_3dEnabled,
            m3d::RenderContext::Mode t_mode,
            m3d::RenderContext::Stereo3dSide t_side,
            m3d::RenderContext::ScreenTarget t_target,
            C3D_Mtx& t_projection,
            C3D_Mtx& t_modelView,
            C3D_LightEnv& t_lightEnv,
            C3D_Light& t_light,
            C3D_LightLut& t_lightLut
        );

        int getProjectionUniform();

        int getModelViewUniform();

        bool is3dEnabled();

        m3d::RenderContext::Mode getMode();

        m3d::RenderContext::Stereo3dSide getSide();

        m3d::RenderContext::ScreenTarget getScreenTarget();

        C3D_Mtx& getProjectionMatrix();

        C3D_Mtx& getModelViewMatrix();

        C3D_LightEnv& getLightEnvironment();

        C3D_Light& getLight();

        C3D_LightLut& getLightLut();

        void enableTextures(bool t_enable);

    private:
        /* data */
        int m_projectionUniformLocation, m_modelViewUniformLocation, m_materialUniformLocation;
        bool m_3dEnabled;
        m3d::RenderContext::Mode m_mode;
        m3d::RenderContext::Stereo3dSide m_side;
        m3d::RenderContext::ScreenTarget m_target;
        C3D_Mtx &m_projection, &m_modelView;
        C3D_LightEnv& m_lightEnv;
        C3D_Light& m_light;
        C3D_LightLut& m_lightLut;
    };
} /* m3d */

#endif /* end of include guard: RENDERCONTEXT_H */
