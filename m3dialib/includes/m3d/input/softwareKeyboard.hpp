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
    enum KeyboardType {
        KEYBOARD_TYPE_NORMAL, ///< Normal keyboard with several pages (QWERTY/accents/symbol/mobile)
        KEYBOARD_TYPE_QWERTY, ///< QWERTY keyboard only
        KEYBOARD_TYPE_NUMPAD, ///< Number pad
        KEYBOARD_TYPE_WESTERN ///< On JPN systems, a text keyboard without Japanese input capabilities, otherwise same as KEYBOARD_TYPE_NORMAL
    };
} /* m3d */


#endif /* end of include guard: SOFTWAREKEYBOARD_H */
