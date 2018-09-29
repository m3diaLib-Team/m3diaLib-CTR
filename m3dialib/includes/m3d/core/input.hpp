/**
 * @file input.hpp
 * @brief Defines the Input class
 */

#ifndef CORE_INPUT_H
#define CORE_INPUT_H

namespace m3d {

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
        static u32 buttonsDown();
        /**
         * @brief Gets the buttons pressed in bits
         * @return Button values in bits
         */
        static u32 buttonsPressed();
        /**
         * @brief Gets the buttons released in bits
         * @return Button values in bits
         */
        static u32 buttonsReleased();
        /**
         * Returns whether the given button is pressed this frame but wasn't pressed in the last frame
         * @param  t_button The button
         * @return          Whether the button is pressed or not
         */
        static bool buttonPressed(Button t_button);
        /**
         * @brief Returns whether the given button is pressed this frame regardless whether it was pressed in the last frame
         * @param  t_button The button
         * @return          Whether the button is pressed or not
         */
        static bool buttonDown(Button t_button);
        /**
         * @brief Returns whether the given button was released (i.e. isn't pressed this frame but was in the last frame)
         * @param  t_button The button
         * @return          Whether the button was released or not
         */
        static bool buttonReleased(Button t_button);

        static int getCirclePadX();

        static int getCirclePadY();

        static int getTouchX();

        static int getTouchY();
    };
}

#endif