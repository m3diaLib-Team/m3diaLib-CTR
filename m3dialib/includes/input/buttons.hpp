/**
 * @file buttons.hpp
 * @brief Implements support for button input
 */
#pragma once
#include <3ds.h>

namespace m3d {
	/**
	 * @brief Namespace for everything button-related
	 */
	namespace buttons {
		/**
		 * @brief Represents the different buttons
		 */
		enum Button {
			BUTTON_A       = BIT(0),       ///< A
			BUTTON_B       = BIT(1),       ///< B
			BUTTON_SELECT  = BIT(2),       ///< Select
			BUTTON_START   = BIT(3),       ///< Start
			BUTTON_DRIGHT  = BIT(4),       ///< D-Pad Right
			BUTTON_DLEFT   = BIT(5),       ///< D-Pad Left
			BUTTON_DUP     = BIT(6),       ///< D-Pad Up
			BUTTON_DDOWN   = BIT(7),       ///< D-Pad Down
			BUTTON_R       = BIT(8),       ///< R
			BUTTON_L       = BIT(9),       ///< L
			BUTTON_X       = BIT(10),      ///< X
			BUTTON_Y       = BIT(11),      ///< Y
			BUTTON_ZL      = BIT(14),      ///< ZL (New 3DS only)
			BUTTON_ZR      = BIT(15),      ///< ZR (New 3DS only)
			BUTTON_TOUCH   = BIT(20),      ///< Touch (Only whether the user presses *somewhere* on the touchscreen)
			BUTTON_CSTICK_RIGHT = BIT(24), ///< C-Stick Right (New 3DS only)
			BUTTON_CSTICK_LEFT  = BIT(25), ///< C-Stick Left (New 3DS only)
			BUTTON_CSTICK_UP    = BIT(26), ///< C-Stick Up (New 3DS only)
			BUTTON_CSTICK_DOWN  = BIT(27), ///< C-Stick Down (New 3DS only)
			BUTTON_CPAD_RIGHT = BIT(28),   ///< Circle Pad Right
			BUTTON_CPAD_LEFT  = BIT(29),   ///< Circle Pad Left
			BUTTON_CPAD_UP    = BIT(30),   ///< Circle Pad Up
			BUTTON_CPAD_DOWN  = BIT(31),   ///< Circle Pad Down
			BUTTON_UP    = BUTTON_DUP    | BUTTON_CPAD_UP,    ///< D-Pad Up or Circle Pad Up
			BUTTON_DOWN  = BUTTON_DDOWN  | BUTTON_CPAD_DOWN,  ///< D-Pad Down or Circle Pad Down
			BUTTON_LEFT  = BUTTON_DLEFT  | BUTTON_CPAD_LEFT,  ///< D-Pad Left or Circle Pad Left
			BUTTON_RIGHT = BUTTON_DRIGHT | BUTTON_CPAD_RIGHT, ///< D-Pad Right or Circle Pad Right
		};

		/**
		 * Returns whether the given button is pressed this frame but wasn't pressed in the last frame
		 * @param  t_buttom The button
		 * @return          Whether the button is pressed or not
		 */
		bool buttonPressed(m3d::buttons::Button t_button);

		/**
		 * @brief Returns whether the given button is pressed this frame regardless whether it was pressed in the last frame
		 * @param  t_buttom The button
		 * @return          Whether the button is pressed or not
		 */
		bool buttonDown(m3d::buttons::Button t_button);

		/**
		 * @brief Returns whether the given button was released (i.e. isn't pressed this frame but was in the last frame)
		 * @param  t_buttom The button
		 * @return          Whether the button was released or not
		 */
		bool buttonReleased(m3d::buttons::Button t_button);
	} /* buttons */
} /* m3d */
