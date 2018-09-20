/**
 * @file drawable.hpp
 * @brief Defines the base class for all drawable classes
 */
#ifndef DRAWABLE_H
#define DRAWABLE_H

#pragma once
#include <citro3d.h>
#include "renderContext.hpp"

namespace m3d {
    /**
     * @brief The base class for all drawable classes.
     *
     * To create your own drawable class, create a child class of this one and implement the draw()-method.
     */
    class Drawable {
    public:
        /**
         * @brief Draws the drawable object
         * @param t_context the RenderContext
         *
         * Implement this function in your own class to draw stuff on the screen using Citro3D/2D-functions.
         */
        virtual void draw(m3d::RenderContext t_context) = 0;
    };
} /* m3d */


#endif /* end of include guard: DRAWABLE_H */
