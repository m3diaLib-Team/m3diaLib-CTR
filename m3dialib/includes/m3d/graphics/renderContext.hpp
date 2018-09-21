/**
 * @file renderContext.hpp
 * @brief Defines the RenderContext-class
 */
#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#pragma once
#include <citro3d.h>

namespace m3d {
    /**
     * @brief The RenderContext-class which holds information about the current rendering process
     */
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

        /**
         * @brief Default constructor
         * @param t_projectionUniform The location of the projection uniform
         * @param t_modelViewUniform  The location of the model view uniform
         * @param t_3dEnabled         Whether stereoscopic 3D is enabled
         * @param t_mode              The current rendering mode
         * @param t_side              The current side for stereoscopic 3D
         * @param t_target            The current screen target
         * @param t_projection        The projection matrix
         * @param t_modelView         The model view matrix
         * @param t_lightEnv          The light environment
         * @param t_light             The light
         * @param t_lightLut          The light LUT
         */
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

        /**
         * @brief Returns the location of the projection uniform
         * @return The location of the uniform
         */
        int getProjectionUniform();

        /**
         * @brief Returns the location of the model view uniform
         * @return The location of the uniform
         */
        int getModelViewUniform();

        /**
         * @brief Returns whether or not stereoscopic 3D is enabled
         * @return Whether or not stereoscopic 3D is enabled
         */
        bool is3dEnabled();

        /**
         * @brief Returns the current rendering mode (flat (2D) or spatial (3D))
         * @return The current mode
         */
        m3d::RenderContext::Mode getMode();

        /**
         * @brief Returns the current side for stereoscopic 3D
         * @return The current side
         */
        m3d::RenderContext::Stereo3dSide getSide();

        /**
         * @brief Returns the current screen target
         * @return The current target
         */
        m3d::RenderContext::ScreenTarget getScreenTarget();

        /**
         * @brief Returns the projection matrix
         * @return The projection matrix
         */
        C3D_Mtx& getProjectionMatrix();

        /**
         * @brief Returns the model view matrix
         * @return The model view matrix
         */
        C3D_Mtx& getModelViewMatrix();

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
         * @brief Enables or disables textures
         * @param t_enable Whether or not to enable textures
         */
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
