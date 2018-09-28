/**
 * @file screen.hpp
 * @brief The master class for drawing on screens
 */
#ifndef SCREEN_H
#define SCREEN_H

#pragma once
#include <citro2d.h>
#include <cstring>
#include <functional>
#include <map>
#include <vector>
#include "camera.hpp"
#include "color.hpp"
#include "drawable.hpp"
#include "renderTarget.hpp"
/**
 * @brief The general m3d-namespace
 */
namespace m3d {
    /**
     * @brief The class used for rendering stuff on a screen
     */
    class Screen {
    public:
        /**
         * @brief Initializes the m3d::Screen object
         * @param t_enable3d Whether to enable stereoscopic 3D by default
         */
        Screen(bool t_enable3d = true);

        /**
         * @brief Destructs the screen object
         */
        ~Screen();

        /**
         * @brief Enables or disables stereoscopic 3D
         * @param t_enabled Whether to enable or disable it
         */
        void set3d(bool t_enabled);

        /**
         * @brief Whether or not to use culling
         * @param t_useCulling Whether to use culling or not
         * @note By default, culling is enabled
         */
        void useCulling(bool t_useCulling);

        /**
         * @brief Returns whether culling is being used or not
         * @return `true` if culling is being used, `false` otherwise
         */
        bool isUsingCulling();

        /**
         * @brief Sets the clear color for both screens
         * @param t_color The color to clear the screen with
         */
        void setClearColor(m3d::Color t_color);

        /**
         * @brief Sets the clear color for one specific screen
         * @param t_color  The color to clear the screen with
         * @param t_target The screen to clear set the color for
         */
        void setClearColor(m3d::Color t_color, m3d::RenderContext::ScreenTarget t_target);

        /**
         * @brief Returns the clear color for the given screen
         * @param  t_target The screen to get the color from
         * @return          The set clear color for the screen
         */
        m3d::Color getClearColor(m3d::RenderContext::ScreenTarget t_target);

        /**
         * @brief Draws something on the top screen
         * @param t_object The object that should be drawn
         * @param t_mode   The drawing-mode
         * @param t_layer The z-inex the object should be drawn at
         */
        void drawTop(m3d::Drawable& t_object, m3d::RenderContext::Mode t_mode = m3d::RenderContext::Mode::Flat, int t_layer = 0);

        /**
         * @brief Draws something on the top screen
         * @param t_object          The object that should be drawn
         * @param t_shadingFunction A function to call right before drawing
         * @param t_mode            The drawing-mode
         * @param t_layer           The z-inex the object should be drawn at
         *
         * @note `t_shadingFunction` allows you to bind your own shaders and to execute your own code. It get's called just before the `draw` method of your drawable gets executed and should return `true` on success. If it returns `false`, the drawable will not be drawn.
         */
        void drawTop(m3d::Drawable& t_object, std::function<bool()> t_shadingFunction, m3d::RenderContext::Mode t_mode = m3d::RenderContext::Mode::Flat, int t_layer = 0);

        /**
         * @brief Draws something on the bottom screen
         * @param t_object The object that should be drawn
         * @param t_mode   The drawing-mode
         * @param t_layer The z-inex the object should be drawn at
         */
        void drawBottom(m3d::Drawable& t_object, m3d::RenderContext::Mode t_mode = m3d::RenderContext::Mode::Flat, int t_layer = 0);

        /**
         * @brief Draws something on the bottom screen
         * @param t_object          The object that should be drawn
         * @param t_shadingFunction A function to call right before drawing
         * @param t_mode            The drawing-mode
         * @param t_layer           The z-inex the object should be drawn at
         *
         * @note `t_shadingFunction` allows you to bind your own shaders and to execute your own code. It get's called just before the `draw` method of your drawable gets executed and should return `true` on success. If it returns `false`, the drawable will not be drawn.
         */
        void drawBottom(m3d::Drawable& t_object, std::function<bool()> t_shadingFunction, m3d::RenderContext::Mode t_mode = m3d::RenderContext::Mode::Flat, int t_layer = 0);

        /**
         * @brief Renders the current screen
         * @param t_clear Whether or not to clear the screens in between frames
         */
        void render(bool t_clear = true);

        /**
         * @brief Returns the width of the screen
         * @param t_target The target screen
         * @return The width of the screen in pixels
         */
        static int getScreenWidth(m3d::RenderContext::ScreenTarget t_target);

        /**
         * @brief Returns the height of the screen
         * @return The height of the screen in pixels
         */
        static int getScreenHeight();

        /**
         * @brief Clears the screen manually
         */
        void clear();

        /**
         * @brief Sets the camera for the given screen target
         * @param t_camera The camera
         * @param t_target The target
         */
        void setCamera(m3d::Camera t_camera, m3d::RenderContext::ScreenTarget t_target);

        /**
         * @brief Returns the camera of the given screen target
         * @param  t_target The target
         * @return          The camera
         */
        m3d::Camera& getCamera(m3d::RenderContext::ScreenTarget t_target);

        /**
         * @brief Sets whether fog should be used for the given screen target
         * @param t_useFog `true` if fog should be used, `false` otherwise for the given screen target
         * @param t_target The target
         */
        void useFog(bool t_useFog, m3d::RenderContext::ScreenTarget t_target);

        /**
         * @brief Returns whether or not fog is being used on the given screen target
         * @param t_target The target
         * @return        `true` if fog is being used, `false` otherwise on the given screen target
         */
        bool getUseFog(m3d::RenderContext::ScreenTarget t_target);

        /**
         * @brief Sets the fog density for the given screen target
         * @param t_density The fog density for the given screen target
         * @param t_target The target
         */
        void setFogDensity(float t_density,m3d::RenderContext::ScreenTarget t_target);

        /**
         * @brief Returns the fog density of the given screen target
         * @param t_target The target
         * @return         The fog density of the given screen target
         */
        float getFogDensity(m3d::RenderContext::ScreenTarget t_target);
    private:
        void prepare();
        void prepareFog(m3d::RenderContext::ScreenTarget t_target);
        void prepareLights(m3d::RenderContext::ScreenTarget t_target);

        /* data */
        int m_projectionUniform, m_modelUniform, m_viewUniform;
        bool m_3dEnabled, m_useCulling;
        m3d::Color m_clearColorTop, m_clearColorBottom;
        m3d::Camera &m_cameraTop, &m_cameraBottom;

        // rendertargets
        m3d::RenderTarget *m_targetTopLeft,
                          *m_targetTopRight,
                          *m_targetBottom;

        // draw stacks
        std::map<int, std::vector<std::pair<m3d::Drawable*, std::function<bool()>>>, std::less<int>> m_drawStackTop2d,
                                                                   m_drawStackTop3d,
                                                                   m_drawStackBottom2d,
                                                                   m_drawStackBottom3d;

        // shader
        DVLB_s* m_dvlb;
        shaderProgram_s m_shader;

        // attribute information
        C3D_AttrInfo m_attributeInfo;

        // matrices
        C3D_Mtx m_projection, m_model, m_view;

        // light
        C3D_LightEnv m_lightEnvTop, m_lightEnvBottom;
        C3D_Light m_lightTop, m_lightBottom;
        C3D_LightLut m_lutPhongTop, m_lutPhongBottom;

        // fog
        bool m_useFogTop, m_useFogBottom;
        float m_fogDensityTop, m_fogDensityBottom;
        C3D_FogLut m_fogLutTop, m_fogLutBottom;
    };
} /* m3d */

#endif /* end of include guard: SCREEN_H */
