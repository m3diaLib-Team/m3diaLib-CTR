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

        /**
         * @brief Returns the position of the circle pad as a direction vector (i.e. polar coordinates)
         * @brief t_useRadians Whether to use radians instead of degrees
         * @return             The vector representing the position of the circlepad
         * @note The first component of the vector represents the angle, the second component represents the length (ranging from 0.f to 1.f)
         */
        m3d::Vector2f getDirectionVector(bool t_useRadians = false);
    } /* circlepad */
} /* m3d */


#endif /* end of include guard: CIRCLEPAD_H */
