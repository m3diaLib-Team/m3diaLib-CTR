/**
 * @file core/input.hpp
 * @brief Defines the Input class
 */
#ifndef CORE_INPUT_H
#define CORE_INPUT_H

#pragma once

namespace m3d {
    /**
     * @brief Handles user input
     */
    class Input {
    public:
        /**
         * @brief Represents the different buttons
         */
        enum Button {
            A           = BIT(0),       ///< A
            B           = BIT(1),       ///< B
            Select      = BIT(2),       ///< Select
            Start       = BIT(3),       ///< Start
            DPadRight   = BIT(4),       ///< D-Pad Right
            DPadLeft    = BIT(5),       ///< D-Pad Left
            DPadUp      = BIT(6),       ///< D-Pad Up
            DPadDown    = BIT(7),       ///< D-Pad Down
            R           = BIT(8),       ///< R
            L           = BIT(9),       ///< L
            X           = BIT(10),      ///< X
            Y           = BIT(11),      ///< Y
            ZL          = BIT(14),      ///< ZL (New 3DS only)
            ZR          = BIT(15),      ///< ZR (New 3DS only)
            Touch       = BIT(20),      ///< Touch (Only whether the user presses *somewhere* on the touchscreen)
            CStickRight = BIT(24),      ///< C-Stick Right (New 3DS only)
            CStickLeft  = BIT(25),      ///< C-Stick Left (New 3DS only)
            CStickUp    = BIT(26),      ///< C-Stick Up (New 3DS only)
            CStickDown  = BIT(27),      ///< C-Stick Down (New 3DS only)
            CPadRight  = BIT(28),       ///< Circle Pad Right
            CPadLeft   = BIT(29),       ///< Circle Pad Left
            CPadUp     = BIT(30),       ///< Circle Pad Up
            CPadDown   = BIT(31),       ///< Circle Pad Down
            Up         = DPadUp    | CPadUp,    ///< D-Pad Up or Circle Pad Up
            Down       = DPadDown  | CPadDown,  ///< D-Pad Down or Circle Pad Down
            Left       = DPadLeft  | CPadLeft,  ///< D-Pad Left or Circle Pad Left
            Right      = DPadRight | CPadRight, ///< D-Pad Right or Circle Pad Right
        };

        /**
         * @brief Gets the buttons down in bits
         * @return Button values in bits
         */
        static inline u32 buttonsDown() {
            return hidKeysHeld();
        }

        /**
         * @brief Gets the buttons pressed in bits
         * @return Button values in bits
         */
        static inline u32 buttonsPressed() {
            return hidKeysDown();
        }

        /**
         * @brief Gets the buttons released in bits
         * @return Button values in bits
         */
        static inline u32 buttonsReleased() {
            return hidKeysUp();
        }

        /**
         * Returns whether the given button is pressed this frame but wasn't pressed in the last frame
         * @param  t_button The button
         * @return          Whether the button is pressed or not
         */
        static inline bool buttonPressed(Button t_button) {
            return (buttonsPressed() & t_button);
        }

        /**
         * @brief Returns whether the given button is pressed this frame regardless whether it was pressed in the last frame
         * @param  t_button The button
         * @return          Whether the button is pressed or not
         */
        static inline bool buttonDown(Button t_button) {
            return (buttonsDown() & t_button);
        }

        /**
         * @brief Returns whether the given button was released (i.e. isn't pressed this frame but was in the last frame)
         * @param  t_button The button
         * @return          Whether the button was released or not
         */
        static inline bool buttonReleased(Button t_button) {
            return (buttonsReleased() & t_button);
        }

        /**
         * @brief Returns the position on the circlepad on the x-axis
         * @return The x-position of the circlepad (ranging from -155 for completely to the left to +155 for completely to the right)
         */
        static inline int getCirclePadX() {
            circlePosition circle;
            hidCircleRead(&circle);
            return circle.dx;
        }

        /**
         * @brief Returns the position on the circlepad on the y-axis
         * @return The y-position of the circlepad (ranging from -155 for completely at the top to +155 for completely at the bottom)
         */
        static inline int getCirclePadY() {
            circlePosition circle;
            hidCircleRead(&circle);
            return circle.dy;
        }

        /**
         * @brief Returns the touch position on the x-axis
         * @return The x-position of the touch input
         */
        static inline int getTouchX() {
            touchPosition touch;
            hidTouchRead(&touch);
            return touch.px;
        }

        /**
         * @brief Returns the touch position on the y-axis
         * @return The y-position of the touch input
         */
        static inline int getTouchY() {
            touchPosition touch;
            hidTouchRead(&touch);
            return touch.py;
        }

        /**
         * @brief Returns a touchPosition of the current touch position
         * @return touchPosition object containing touch info
         */
        static inline touchPosition getTouch() {
            touchPosition touch;
            hidTouchRead(&touch);
            return touch;
        }

        /**
         * @brief Returns current angular rate of gyroscope
         * @return libctru angularRate object containing gyro info
         */
        static inline angularRate getGyro() {
            angularRate rate;
            hidGyroRead(&rate);
            return rate;
        }

        // getGyroX();

        // getGyroY();
    };
}

#endif
