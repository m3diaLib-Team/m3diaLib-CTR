/**
 * @file drawable.hpp
 * @brief Defines the base class for all drawable classes
 */
#pragma once
#include <3ds.h>
#include <citro3d.h>

namespace m3d {
    /**
     * @brief The base class for all drawable classes.
     *
     * To create your own drawable class, create a child class of this one and implement the draw()-function.
     */
    class Drawable {
    public:
        /**
         * @brief Draws the drawable object
         * @param t_side The current 3D side (0 = left, 1 = right)
         * @param t_projection The projection uniform of the shader
         * @param t_transform The transform uniform of the shader
         * @param t_useTransform The useTransform uniform of the shader
         *
         * Implement this function in your own class to draw stuff on the screen using Citro3D-functions.
         */
        virtual void draw(int t_side, int t_projection, int t_transform, int t_useTransform) = 0;
    };
} /* m3d */
