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
        );

        int getProjectionUniform();

        int getModelViewUniform();

        int getLightVecUniform();

        int getLightHalfVecUniform();

        int getLightColorUniform();

        int getMaterialUniform();

        bool is3dEnabled();

        m3d::RenderContext::Mode getMode();

        m3d::RenderContext::Stereo3dSide getSide();

        m3d::RenderContext::ScreenTarget getScreenTarget();

        C3D_Mtx& getProjectionMatrix();

        C3D_Mtx& getModelViewMatrix();

        void enableTextures(bool t_enable);

    private:
        /* data */
        int m_projectionUniformLocation, m_modelViewUniformLocation, m_lightVecUniformLocation, m_lightHalfVecUniformLocation, m_lightColorUniformLocation, m_materialUniformLocation;
        bool m_3dEnabled;
        m3d::RenderContext::Mode m_mode;
        m3d::RenderContext::Stereo3dSide m_side;
        m3d::RenderContext::ScreenTarget m_target;
        C3D_Mtx &m_projection, &m_modelView;
    };
} /* m3d */

#endif /* end of include guard: RENDERCONTEXT_H */
