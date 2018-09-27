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

        SoftwareKeyboard();

        void setValidator(std::function<void(m3d::SoftwareKeyboard::KeyboardEvent&)> t_validator);

        void setButtonNumber(int t_number);

        int getButtonNumber();

        void setFixedLength(int t_length);

        int getFixedLength();

        void allowEmpty(bool t_allow);

        bool getAllowEmpty();

        void allowBlank(bool t_allow);

        bool getAllowBlank();

        void setPredictive(bool t_enable);

        bool isPredictive();

        void enableMultiline(bool t_enable);

        bool isMultiline();

        void darkenTop(bool t_enable);

        bool getDarkenTop();

        void allowHome(bool t_allow);

        bool getAllowHome();

        void setButtonSubmit(bool t_submit, m3d::SoftwareKeyboard::Button t_button);

        bool getButtonSubmit(m3d::SoftwareKeyboard::Button t_button);

        void setHintText(const std::string& t_text);

        std::string getHintText();

        void setInitialText(const std::string& t_text);

        std::string getInitialText();

        void setButtonText(const std::string& t_text, m3d::SoftwareKeyboard::Button t_button);

        std::string getButtonText(m3d::SoftwareKeyboard::Button t_button);

        void setKeyboardType(m3d::SoftwareKeyboard::KeyboardType t_keyboardType);

        m3d::SoftwareKeyboard::KeyboardType getKeyboardType();

        void setPasswordMode(m3d::SoftwareKeyboard::PasswordMode t_passwordMode);

        m3d::SoftwareKeyboard::PasswordMode getPasswordMode();

        void display();

        std::string getLastInput();

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
