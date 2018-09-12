/**
 * @file softwareKeyboard.hpp
 * @brief Defines the m3d::SoftwareKeyboard class
 */
#ifndef SOFTWAREKEYBOARD_H
#define SOFTWAREKEYBOARD_H

#pragma once

namespace m3d {
    /**
     * @brief Defines which type of keyboard to show
     */
    enum class KeyboardType {
        Normal, ///< Normal keyboard with several pages (QWERTY/accents/symbol/mobile)
        Qwerty, ///< QWERTY keyboard only
        Numpad, ///< Number pad
        Western ///< On JPN systems, a text keyboard without Japanese input capabilities, otherwise same as KEYBOARD_TYPE_NORMAL
    };
} /* m3d */


#endif /* end of include guard: SOFTWAREKEYBOARD_H */
