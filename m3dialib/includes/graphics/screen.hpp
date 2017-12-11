/**
 * @file screen.hpp
 * @brief The master class for drawing on screens
 */
#pragma once
#include <vector>
#include <map>
#include <cstring>
#include <3ds.h>
#include <citro3d.h>
#include "./renderTarget.hpp"
#include "./drawable.hpp"

/**
 * @brief The general m3d-namespace
 */
namespace m3d {
    /**
     * @brief Defines the screen targets (top/bottom)
     */
    enum ScreenTarget {
        SCREEN_TOP,     ///< Top screen
        SCREEN_BOTTOM   ///< Bottom/touch screen
    };

    /**
     * @brief Defines the two sides in stereoscopic 3D mode
     */
    enum Stereo3dSide {
        SIDE_LEFT = 0, ///< Left side
        SIDE_RIGHT = 1 ///< Right side
    };

    /**
     * @brief The class used for rendering stuff on a screen
     */
    class Screen {
    public:
        /**
         * @brief Initializes the m3d::Screen object
         * @param t_enable3d Whether to enable stereoscopic 3D by default
         */
        Screen(bool t_enable3d = false);

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
         * @brief Force-clears the screen by resetting all framebuffers of the screen
         */
        void forceClear();

        /**
         * @brief Returns the projection uniform of the shader
         * @return The uniform
         */
        int getProjectionUniform();

        /**
         * @brief Returns the transform uniform of the shader
         * @return The uniform
         */
        int getTransformUniform();

        /**
         * @brief Returns the useTransform uniform of the shader
         * @return The uniform
         */
        int getUseTransformUniform();

        /**
         * @brief Clears the screen
         */
        void clear();

        /**
         * Draws something on the top screen
         * @param t_object The object that should be drawn
         * @param t_layer The z-inex the object should be drawn at
         */
        void drawTop(m3d::Drawable& t_object, int t_layer = 0);

        /**
         * Draws something on the bottom screen
         * @param t_object The object that should be drawn
         * @param t_layer The z-inex the object should be drawn at
         */
        void drawBottom(m3d::Drawable& t_object, int t_layer = 0);

        /**
         * @brief Renders the current screen
         */
        void render();

        /**
         * @brief Returns the width of the screen
         * @param t_target The target screen
         * @return The width of the screen in pixels
         */
        int getScreenWidth(m3d::ScreenTarget t_target);

        /**
         * @brief Returns the height of the screen
         * @return The height of the screen in pixels
         */
        int getScreenHeight();

    private:
        /* data */
        m3d::RenderTarget *m_targetTopLeft, *m_targetTopRight, *m_targetBottom;
        std::map<int, std::vector<m3d::Drawable*>, std::greater<int>> m_drawStackTop, m_drawStackBottom;
        bool m_3dEnabled;
        DVLB_s *m_dvlb;
        shaderProgram_s m_shader;
        int m_projection, m_transform, m_useTransform;

    };
} /* m3d */
