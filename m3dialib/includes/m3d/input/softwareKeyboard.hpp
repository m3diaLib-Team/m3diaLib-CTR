/**
 * @file softwareKeyboard.hpp
 * @brief Defines the SoftwareKeyboard class
 */
#ifndef SOFTWAREKEYBOARD_H
#define SOFTWAREKEYBOARD_H

#pragma once
#include <3ds.h>
#include <functional>
#include <string>
#include <vector>

namespace m3d {
    /**
     * @brief The SoftwareKeyboard-class, used for displaying the 3DS's software keyboard
     */
    class SoftwareKeyboard {
    public:
        /**
         * @brief Defines which type of keyboard to show
         */
        enum class KeyboardType {
            Normal, ///< Normal keyboard with several pages (QWERTY/accents/symbol/mobile)
            Qwerty, ///< QWERTY keyboard only
            Numpad, ///< Number pad
            Western ///< On Japanese systems, a text keyboard without Japanese input capabilities, otherwise same as `Normal`
        };

        /**
         * @brief Defines the three keyboard buttons
         */
        enum class Button {
            Left,   ///< Left button (usually displays "Cancel")
            Middle, ///< Middle button (usually displays "I forgot")
            Right,  ///< Right button (usually displays "OK")
            None    ///< No button (shouldn't happen in most cases)
        };

        /**
         * @brief Defines the keyboard's password modes
         */
        enum class PasswordMode {
            None, ///< Doesn't hide the characters
            Hide, ///< Hides the characters immediatley
            Delay ///< Hides the characters after a second
        };

        /**
         * @brief A keyboard event which will get passed to a validator
         */
        class KeyboardEvent {
        public:
            /**
             * @brief Constructs the KeyboardEvent with the given text
             * @param t_text The text
             */
            KeyboardEvent(const std::string t_text);

            /**
             * @brief Displays an error message and then continues the text input
             * @param t_message The message to display
             */
            void error(const char* t_message);

            /**
             * @brief Displays an error message and then closes the text input
             * @param t_message The message to display
             */
            void close(const char* t_message);

            /**
             * @brief Marks the input as valid and closes the text input
             */
            void valid();

            /**
             * @brief Returns the text entered by the user
             * @return The text
             */
            std::string getText();

            #ifndef DOXYGEN_SKIP
            SwkbdCallbackResult getResult();
            const char* getMessage();
            #endif

        private:
            /* data */
            std::string m_text;
            const char* m_message;
            SwkbdCallbackResult m_callbackResult;
        };

        /**
         * @brief Default constructor
         */
        SoftwareKeyboard();

        /**
         * @brief Sets a validation callback
         * @param t_validator The callback
         */
        void setValidator(std::function<void(m3d::SoftwareKeyboard::KeyboardEvent&)> t_validator);

        /**
         * @brief Sets the number of buttons to display at the bottom of the keyboard
         * @param t_number The number of buttons, ranging from 1 to 3
         */
        void setButtonNumber(int t_number);

        /**
         * @brief Returns the number of buttons displayed at the bottom of the keyboard
         * @return The number of buttons
         */
        int getButtonNumber();

        /**
         * @brief Sets the maximum length of the input
         * @param t_length The length (-1 for no limit)
         */
        void setFixedLength(int t_length);

        /**
         * @brief Returns the maximum length of the input
         * @return The length
         */
        int getFixedLength();

        /**
         * @brief Sets whether or not to allow empty input (no characters)
         * @param t_allow `true` if empty input is allowed, `false` otherwise
         */
        void allowEmpty(bool t_allow);

        /**
         * @brief Returns whether or not empty input is allowed
         * @return `true` if empty input is allowed, `false` otherwise
         */
        bool getAllowEmpty();

        /**
         * @brief Sets whether or not to allow blank input (only whitespace characters)
         * @param t_allow `true` if blank input is allowed, `false` otherwise
         */
        void allowBlank(bool t_allow);

        /**
         * @brief Returns whether or not blank input is allowed
         * @return `true` if blank input is allowed, `false` otherwise
         */
        bool getAllowBlank();

        /**
         * @brief Whether or not to enable predictive input
         * @param t_enable `true` if predictive input is enabled, `false` otherwise
         */
        void setPredictive(bool t_enable);

        /**
         * @brief Returns whether or not predictive input is enabled
         * @return true` if predictive input is enabled, `false` otherwise
         */
        bool isPredictive();

        /**
         * @brief Whether or not to enable multiline input
         * @param t_enable `true` if multiline input should be enabled, `false` otherwise
         */
        void enableMultiline(bool t_enable);

        /**
         * @brief Returns whether or not multiline input is enabled
         * @return true` if multiline input is enabled, `false` otherwise
         */
        bool isMultiline();

        /**
         * @brief Sets whether or not the top screen should be darkened
         * @param t_enable `true` to darken it, `false` otherwise
         */
        void darkenTop(bool t_enable);

        /**
         * @brief Returns whether the top screen gets darkened or not
         * @return `true` if it gets darkened, `false` otherwise
         */
        bool getDarkenTop();

        /**
         * @brief Sets whether or not to allow the home button
         * @param t_allow `true` if the home button should be allowed, `false` otherwise
         */
        void allowHome(bool t_allow);

        /**
         * @brief Returns whether the home button is allowed or not
         * @return `true` if the home button is allowed, `false` otherwise
         */
        bool getAllowHome();

        /**
         * @brief Sets whether or not the given button should act as a submit button
         * @param t_submit `true` if it should act as a submit button, `false` if it should act as a cancel button
         * @param t_button The button
         */
        void setButtonSubmit(bool t_submit, m3d::SoftwareKeyboard::Button t_button);

        /**
         * @brief Returns whether or not the given button acts as a submit button
         * @param  t_button The button
         * @return          `true` if it acts as a submit button, `false` if it acts as a cancel button
         */
        bool getButtonSubmit(m3d::SoftwareKeyboard::Button t_button);

        /**
         * @brief Sets the hint text (the placeholder)
         * @param t_text The hint text
         */
        void setHintText(const std::string& t_text);

        /**
         * @brief Returns the hint text
         * @return The hint text
         */
        std::string getHintText();

        /**
         * @brief Sets the initial text
         * @param t_text The initial text
         */
        void setInitialText(const std::string& t_text);

        /**
         * @brief Returns the initial text
         * @return The initial text
         */
        std::string getInitialText();

        /**
         * @brief Sets the label for the given button
         * @param t_text   The text
         * @param t_button The button
         */
        void setButtonText(const std::string& t_text, m3d::SoftwareKeyboard::Button t_button);

        /**
         * @brief Returns the label of the given button
         * @param  t_button The button
         * @return          The label
         */
        std::string getButtonText(m3d::SoftwareKeyboard::Button t_button);

        /**
         * @brief Sets the type of the keyboard
         * @param t_keyboardType The keyboard type
         */
        void setKeyboardType(m3d::SoftwareKeyboard::KeyboardType t_keyboardType);

        /**
         * @brief Returns the type of the keyboard
         * @return The keyboard type
         */
        m3d::SoftwareKeyboard::KeyboardType getKeyboardType();

        /**
         * @brief Sets the password mode for the keyboard
         * @param t_passwordMode The password mode
         */
        void setPasswordMode(m3d::SoftwareKeyboard::PasswordMode t_passwordMode);

        /**
         * @brief Returns the password mode of the keyboard
         * @return The password mode
         */
        m3d::SoftwareKeyboard::PasswordMode getPasswordMode();

        /**
         * @brief Displays the keyboard
         */
        void display();

        /**
         * @brief Returns the latest input
         * @return The input
         */
        std::string getLastInput();

        /**
         * @brief Returns the last pressed button
         * @return The id of the last pressed button (ranging from 1 to 3)
         */
        m3d::SoftwareKeyboard::Button getLastButton();

    private:
        static SwkbdCallbackResult callback(void* t_user, const char** t_ppMessage, const char* t_text, size_t t_textlen);

        /* data */
        int m_numButtons, m_fixedLength;
        bool m_allowEmpty, m_allowBlank, m_predictive, m_multiline, m_darkenTop, m_allowHome, m_leftButtonSubmit, m_middleButtonSubmit, m_rightButtonSubmit;
        std::string m_initialText, m_hintText, m_buttonLeftText, m_buttonMiddleText, m_buttonRightText;
        m3d::SoftwareKeyboard::KeyboardType m_keyboardType;
        m3d::SoftwareKeyboard::PasswordMode m_passwordMode;
        std::function<void(m3d::SoftwareKeyboard::KeyboardEvent&)> m_validator;

        // last input
        std::string m_lastText;
        m3d::SoftwareKeyboard::Button m_lastButton;
    };
} /* m3d */


#endif /* end of include guard: SOFTWAREKEYBOARD_H */
