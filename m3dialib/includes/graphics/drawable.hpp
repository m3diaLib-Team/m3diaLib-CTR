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
         *
         * Implement this function in your own class to draw stuff on the screen using Citro2D-functions.
         */
        virtual void draw(int t_side) = 0;
    };
} /* m3d */
