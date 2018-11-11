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
         * @brief Adds a vertex to the current vertex buffer
         * @param t_posX    The x-position
         * @param t_posY    The y-position
         * @param t_posZ    The z-position
         * @param t_u       The u-value
         * @param t_v       The v-value
         * @param t_normalX The x-value of the normal
         * @param t_normalY The y-value of the normal
         * @param t_normalZ The z-value of the normal
         * @param t_blend   The blend value (useless in 3D mode)
         * @param t_color   The color (in 3D mode, onle the alpha-component will be used)
         */
        void addVertex(int t_posX, int t_posY, int t_posZ,
                       int t_u, int t_v,
                       int t_normalX, int t_normalY, int t_normalZ,
                       float t_blend,
                       m3d::Color t_color);

        /**
         * @brief Returns the current rendering mode (flat (2D) or spatial (3D))
         * @return The current mode
        */
        m3d::RenderContext::Mode getMode();

        /**
         * @brief Sets the rendering mode to use
         * @param t_mode The rendering mode
         */
        void useMode(m3d::RenderContext::Mode t_mode);

        /**
         * @brief Binds a texture to use
         * @param t_texture The texture
         * @param t_texEnv  The texture-environment to use
         */
        void bindTexture(const m3d::Texture& t_texture, int t_texEnv = 0);

        /**
         * @brief Flushes the vertex buffer's content to the GPU (and thereby draws the vertices)
         */
        void flush();

        /**
         * @brief Enables or disables textures
         * @param t_enable Whether or not to enable textures
         * @deprecated This method is deprecated. Use m3d::RenderContext::bindTexture instead
         */
        [[deprecated]] void enableTextures(bool t_enable);

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
