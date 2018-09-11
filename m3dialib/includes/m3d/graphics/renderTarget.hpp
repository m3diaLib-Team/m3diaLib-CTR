/**
 * @file renderTarget.hpp
 * @brief Defines the RenderTarget class
 */
#pragma once
#include <citro3d.h>

namespace m3d {
    /**
     * @brief The RenderTarget class, used for drawing stuff onto
     * @todo Implement drawing support
     */
    class RenderTarget {
    public:
        /**
         * @brief Creates a render target
         * @param t_width  The width of the target
         * @param t_height The height of the target
         */
        RenderTarget(int t_width, int t_height);

        /**
         * @brief Creates a render target
         * @param t_width  The width of the target
         * @param t_height The height of the target
         * @param t_screen The screen (GFX_TOP or GFX_BOTTOM)
         * @param t_side   The side (GFX_LEFT or GFX_RIGHT)
         */
        RenderTarget(int t_width, int t_height, gfxScreen_t t_screen, gfx3dSide_t t_side);

        /**
         * @brief Returns the render target
         * @return The render target
         */
        C3D_RenderTarget* getRenderTarget();

        /**
         * @brief Returns the projection matrix of this render target
         * @return The projection matrix
         */
        C3D_Mtx* getProjectionMatrix();

        /**
         * @brief Returns the width of this render target
         * @return The width of the render target
         */
        int getWidth();

        /**
         * @brief Returns the height of this render target
         * @return The height of the render target
         */
        int getHeight();

        /**
         * @brief Sets the clear color of the render target
         * @param t_color The color
         * @todo Implement support for m3d::Color
         */
        void setClearColor(u32 t_color);

        /**
         * @brief Returns the current clear color
         * @return The color
         * @todo Implement support for m3d::Color
         */
        u32 getClearColor();

    private:
        /* data */
        C3D_RenderTarget* m_target;
        C3D_Mtx m_projection;
        int m_width, m_height;
        u32 m_clearColor;

    };
} /* m3d */
