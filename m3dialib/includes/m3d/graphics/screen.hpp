/**
 * @file screen.hpp
 * @brief The master class for drawing on screens
 */
#ifndef SCREEN_H
#define SCREEN_H

#pragma once
#include <vector>
#include <map>
#include <cstring>
#include <citro2d.h>
#include "renderTarget.hpp"
#include "drawable.hpp"
#include "color.hpp"

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
         * @brief Defines the screen targets (top/bottom)
         */
        enum ScreenTarget {
            Top,     ///< Top screen
            Bottom   ///< Bottom/touch screen
        };

        /**
         * @brief Defines the two sides in stereoscopic 3D mode
         */
        enum Stereo3dSide {
            Left  = 0, ///< Left side
            Right = 1  ///< Right side
        };

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
         * @brief Sets the clear color for both screens
         * @param t_color The color to clear the screen with
         */
        void setClearColor(m3d::Color t_color);

        /**
         * @brief Sets the clear color for one specific screen
         * @param t_color  The color to clear the screen with
         * @param t_target The screen to clear set the color for
         */
        void setClearColor(m3d::Color t_color, m3d::Screen::ScreenTarget t_target);

        /**
         * @brief Returns the clear color for the given screen
         * @param  t_target The screen to get the color from
         * @return          The set clear color for the screen
         */
        m3d::Color getClearColor(m3d::Screen::ScreenTarget t_target);

        /**
         * @brief Draws something on the top screen
         * @param t_object The object that should be drawn
         * @param t_layer The z-inex the object should be drawn at
         */
        void drawTop(m3d::Drawable& t_object, int t_layer = 0);

        /**
         * @brief Draws something on the bottom screen
         * @param t_object The object that should be drawn
         * @param t_layer The z-inex the object should be drawn at
         */
        void drawBottom(m3d::Drawable& t_object, int t_layer = 0);

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
        static int getScreenWidth(m3d::Screen::ScreenTarget t_target);

        /**
         * @brief Returns the height of the screen
         * @return The height of the screen in pixels
         */
        static int getScreenHeight();

    private:
        void clear();

        /* data */
        int m_projection, m_transform, m_useTransform;
        bool m_3dEnabled;
        m3d::Color m_clearColorTop, m_clearColorBottom;
        m3d::RenderTarget *m_targetTopLeft, *m_targetTopRight, *m_targetBottom;
        std::map<int, std::vector<m3d::Drawable*>, std::less<int>> m_drawStackTop, m_drawStackBottom;
        DVLB_s *m_dvlb;
        shaderProgram_s m_shader;

    };
} /* m3d */

#endif /* end of include guard: SCREEN_H */
