/**
 * @file input.hpp
 * @brief Defines the Input class
 */
#ifndef INPUT_H
#define INPUT_H

namespace m3d {

    class Input {
    public:
        /**
         * @brief Gets the buttons down in bits
         * @return Button values in bits 
         */
        u32 buttonsDown();
        /**
         * @brief Gets the buttons pressed in bits
         * @return Button values in bits
         */
        u32 buttonsPressed();
        /**
         * @brief Gets the buttons released in bits
         * @return Button values in bits
         */
        u32 buttonsReleased();
        /**
         * Returns whether the given button is pressed this frame but wasn't pressed in the last frame
         * @param  t_button The button
         * @return          Whether the button is pressed or not
         */
        bool buttonPressed(m3d::buttons::Button t_button);
        /**
         * @brief Returns whether the given button is pressed this frame regardless whether it was pressed in the last frame
         * @param  t_button The button
         * @return          Whether the button is pressed or not
         */
        bool buttonDown(m3d::buttons::Button t_button);
        /**
         * @brief Returns whether the given button was released (i.e. isn't pressed this frame but was in the last frame)
         * @param  t_button The button
         * @return          Whether the button was released or not
         */
        bool buttonReleased(m3d::buttons::Button t_button);
    };
}

#endif