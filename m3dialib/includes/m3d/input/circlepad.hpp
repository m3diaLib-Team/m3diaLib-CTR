/**
 * @file circlepad.hpp
 * @brief Implements support for circlepad input
 */
#ifndef CIRCLEPAD_H
#define CIRCLEPAD_H

#pragma once
#include <3ds.h>
#include "m3d/graphics/vertex.hpp"

namespace m3d {
    /**
     * @brief Namespace for everything circlepad related
     */
    namespace circlepad {
        /**
         * @brief Returns the current circlepad x position (ranging from -155 for completely to the left to +155 for completely to the right)
         * @return The curent x position of the circlepad
         */
        int getXPosition();

        /**
         * @brief Returns the current circlepad y position (ranging from -155 for completely at the top to +155 for completely at the bottom)
         * @return The curent y position of the circlepad
         */
        int getYPosition();
    } /* circlepad */
} /* m3d */


#endif /* end of include guard: CIRCLEPAD_H */
