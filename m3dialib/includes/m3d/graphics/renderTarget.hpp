/**
 * @file renderTarget.hpp
 * @brief Defines the RenderTarget class
 */
#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#pragma once
#include <citro2d.h>

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
         * @brief Returns the render target
         * @return The render target
         */
        C3D_RenderTarget* getRenderTarget();

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
         * @brief Clears the rendertarget
         */
        void clear();

        /**
         * @brief Returns the current clear color
         * @return The color
         * @todo Implement support for m3d::Color
         */
        u32 getClearColor();

    private:
        /* data */
        int m_width, m_height;
        u32 m_clearColor;
        C3D_RenderTarget* m_target;

    };
} /* m3d */

#endif /* end of include guard: RENDERTARGET_H */
