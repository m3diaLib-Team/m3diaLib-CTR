/**
 * @file touch.hpp
 * @brief Implements support for touch input
 */
#ifndef TOUCH_H
#define TOUCH_H

#pragma once
#include <3ds.h>

namespace m3d {
    /**
     * @brief Namespace for everything touch related
     */
    namespace touch {
        /**
         * @brief Returns the current touch x position
         * @return The curent x position of the touch input
         */
        int getXPosition();

        /**
         * @brief Returns the current touch y position
         * @return The curent y position of the touch input
         */
        int getYPosition();
    } /* touch */
} /* m3d */


#endif /* end of include guard: TOUCH_H */
