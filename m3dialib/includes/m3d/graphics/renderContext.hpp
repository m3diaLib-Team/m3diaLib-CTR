/**
 * @file renderContext.hpp
 * @brief Defines the RenderContext-class
 */
#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#pragma once
#include <citro3d.h>

namespace m3d {
    class Color;
    class Screen;
    class Texture;

    /**
     * @brief The RenderContext-class which holds information about the current rendering process
     */
    class RenderContext {
    friend class Screen;
    public:
        /**
         * @brief Defines different possible render targets
         */
        enum class RenderTarget {
            Top,          ///< Top screen
            Bottom,       ///< Bottom/touch screen#
            RenderTarget, ///< A m3d::RenderTarget
            Stencil       ///< The stencil buffer
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

    private:
        RenderContext(
            int t_modelUniform,
            bool t_3dEnabled,
            m3d::RenderContext::Mode t_mode,
            m3d::RenderContext::Stereo3dSide t_side,
            m3d::RenderContext::RenderTarget t_target,
            C3D_Mtx& t_model,
            C3D_LightEnv& t_lightEnv,
            C3D_Light& t_light,
            C3D_LightLut& t_lightLut
        );

    public:
        /**
         * @brief Returns the location of the model view uniform
         * @return The location of the uniform
         */
        int getModelUniform();

        /**
         * @brief Returns whether or not stereoscopic 3D is enabled
         * @return Whether or not stereoscopic 3D is enabled
         */
        bool is3dEnabled();

        /**
         * @brief Returns the current side for stereoscopic 3D
         * @return The current side
         */
        m3d::RenderContext::Stereo3dSide getSide();

        /**
         * @brief Returns the current screen target
         * @return The current target
         */
        m3d::RenderContext::RenderTarget getRenderTarget();

        /**
         * @brief Returns the model matrix
         * @return The model matrix
         */
        C3D_Mtx& getModelMatrix();

        /**
         * @brief Returns the light environment
         * @return The light environment
         */
        C3D_LightEnv& getLightEnvironment();

        /**
         * @brief Returns the light
         * @return The light
         */
        C3D_Light& getLight();

        /**
         * @brief Returns the light LUT
         * @return The light LUT
         */
        C3D_LightLut& getLightLut();

        /**
         * @brief Returns the current rendering mode (flat (2D) or spatial (3D))
         * @return The current mode
        */
        m3d::RenderContext::Mode getMode();

    private:
        /* data */
        int m_modelUniformLocation;
        bool m_3dEnabled;
        static bool m_texturesEnabled;
        m3d::RenderContext::Mode m_mode;
        m3d::RenderContext::Stereo3dSide m_side;
        m3d::RenderContext::RenderTarget m_target;
        C3D_Mtx &m_model;
        C3D_LightEnv& m_lightEnv;
        C3D_Light& m_light;
        C3D_LightLut& m_lightLut;
    };
} /* m3d */

#endif /* end of include guard: RENDERCONTEXT_H */
