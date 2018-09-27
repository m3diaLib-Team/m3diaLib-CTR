#include "m3d/input/softwareKeyboard.hpp"
#include "m3d/private/input.hpp"
#include "stdio.h"

namespace m3d {
    SoftwareKeyboard::SoftwareKeyboard() :
        m_numButtons(3),
        m_allowEmpty(true),
        m_allowBlank(true),
        m_predictive(false),
        m_multiline(false),
        m_darkenTop(false),
        m_leftButtonSubmit(false),
        m_middleButtonSubmit(false),
        m_rightButtonSubmit(true),
        m_initialText(""),
        m_hintText(""),
        m_buttonLeftText("Cancel"),
        m_buttonMiddleText("I forgot"),
        m_buttonRightText("OK"),
        m_keyboardType(m3d::SoftwareKeyboard::KeyboardType::Normal),
        m_passwordMode(m3d::SoftwareKeyboard::PasswordMode::None),
        m_validator([](m3d::SoftwareKeyboard::KeyboardEvent& evt){evt.valid();}),
        m_lastText(""),
        m_lastButton(m3d::SoftwareKeyboard::Button::None) { /* do nothing */ }

    void SoftwareKeyboard::setValidator(std::function<void(m3d::SoftwareKeyboard::KeyboardEvent&)> t_validator) {
        m_validator = t_validator;
    }

    void SoftwareKeyboard::setButtonNumber(int t_number) {
        m_numButtons = t_number;
    }

    int SoftwareKeyboard::getButtonNumber() {
        return m_numButtons;
    }

    void SoftwareKeyboard::allowEmpty(bool t_allow) {
        m_allowEmpty = t_allow;
    }

    bool SoftwareKeyboard::getAllowEmpty() {
        return m_allowEmpty;
    }

    void SoftwareKeyboard::allowBlank(bool t_allow) {
        m_allowBlank = t_allow;
    }

    bool SoftwareKeyboard::getAllowBlank() {
        return m_allowBlank;
    }

    void SoftwareKeyboard::setPredictive(bool t_enable) {
        m_predictive = t_enable;
    }

    bool SoftwareKeyboard::isPredictive() {
        return m_predictive;
    }

    void SoftwareKeyboard::enableMultiline(bool t_enable) {
        m_multiline = t_enable;
    }

    bool SoftwareKeyboard::isMultiline() {
        return m_multiline;
    }

    void SoftwareKeyboard::darkenTop(bool t_enable) {
        m_darkenTop = t_enable;
    }

    bool SoftwareKeyboard::getDarkenTop() {
        return m_darkenTop;
    }

    void SoftwareKeyboard::allowHome(bool t_allow) {
        m_allowHome = t_allow;
    }

    bool SoftwareKeyboard::getAllowHome() {
        return m_allowHome;
    }

    void SoftwareKeyboard::setButtonSubmit(bool t_submit, m3d::SoftwareKeyboard::Button t_button) {
        switch (t_button) {
            case m3d::SoftwareKeyboard::Button::Left:
                m_leftButtonSubmit = t_submit;
                break;
            case m3d::SoftwareKeyboard::Button::Middle:
                m_middleButtonSubmit = t_submit;
                break;
            case m3d::SoftwareKeyboard::Button::Right:
                m_rightButtonSubmit = t_submit;
            default:
                return;
        }
    }

    bool SoftwareKeyboard::getButtonSubmit(m3d::SoftwareKeyboard::Button t_button) {
        switch (t_button) {
            case m3d::SoftwareKeyboard::Button::Left:
                return m_leftButtonSubmit;
                break;
            case m3d::SoftwareKeyboard::Button::Middle:
                return m_middleButtonSubmit;
                break;
            case m3d::SoftwareKeyboard::Button::Right:
                return m_rightButtonSubmit;
                break;
            default:
                return false;
        }
    }

    void SoftwareKeyboard::setHintText(const std::string& t_text) {
        m_hintText = t_text;
    }

    std::string SoftwareKeyboard::getHintText() {
        return m_hintText;
    }

    void SoftwareKeyboard::setInitialText(const std::string& t_text) {
        m_initialText = t_text;
    }

    std::string SoftwareKeyboard::getInitialText() {
        return m_initialText;
    }

    void SoftwareKeyboard::setButtonText(const std::string& t_text, m3d::SoftwareKeyboard::Button t_button) {
        switch (t_button) {
            case m3d::SoftwareKeyboard::Button::Left:
                m_buttonLeftText = t_text;
                break;
            case m3d::SoftwareKeyboard::Button::Middle:
                m_buttonMiddleText = t_text;
                break;
            case m3d::SoftwareKeyboard::Button::Right:
                m_buttonRightText = t_text;
            default:
                return;
        }
    }

    std::string SoftwareKeyboard::getButtonText(m3d::SoftwareKeyboard::Button t_button) {
        switch (t_button) {
            case m3d::SoftwareKeyboard::Button::Left:
                return m_buttonLeftText;
                break;
            case m3d::SoftwareKeyboard::Button::Middle:
                return m_buttonMiddleText;
                break;
            case m3d::SoftwareKeyboard::Button::Right:
                return m_buttonRightText;
                break;
            default:
                return "";
        }
    }

    void SoftwareKeyboard::setKeyboardType(m3d::SoftwareKeyboard::KeyboardType t_keyboardType) {
        m_keyboardType = t_keyboardType;
    }

    m3d::SoftwareKeyboard::KeyboardType SoftwareKeyboard::getKeyboardType() {
        return m_keyboardType;
    }

    void SoftwareKeyboard::setPasswordMode(m3d::SoftwareKeyboard::PasswordMode t_passwordMode) {
        m_passwordMode = t_passwordMode;
    }

    m3d::SoftwareKeyboard::PasswordMode SoftwareKeyboard::getPasswordMode() {
        return m_passwordMode;
    }

    void SoftwareKeyboard::display() {
        m3d::priv::input::keyboardValidator = m_validator;

        SwkbdState swkbd;
        char buffer[2048];

        swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 3, -1);
        swkbdSetHintText(&swkbd, m_hintText.c_str());
        swkbdSetInitialText(&swkbd, m_initialText.c_str());

        swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, m_buttonLeftText.c_str(), m_leftButtonSubmit);
        swkbdSetButton(&swkbd, SWKBD_BUTTON_MIDDLE, m_buttonMiddleText.c_str(), m_middleButtonSubmit);
        swkbdSetButton(&swkbd, SWKBD_BUTTON_RIGHT, m_buttonRightText.c_str(), m_rightButtonSubmit);

        swkbdSetFeatures(&swkbd,
            (m_predictive ? SWKBD_PREDICTIVE_INPUT : 0) |
            (m_darkenTop ? SWKBD_DARKEN_TOP_SCREEN : 0) |
            (m_multiline ? SWKBD_MULTILINE : 0) |
            (m_allowHome ? SWKBD_ALLOW_HOME : 0)
        );

        if (!m_allowBlank && !m_allowEmpty) {
            swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 2048);
        } else if (!m_allowBlank) {
            swkbdSetValidation(&swkbd, SWKBD_NOTBLANK, 0, 2048);
        } else if (!m_allowEmpty) {
            swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY, 0, 2048);
        }

        switch (m_passwordMode) {
            case m3d::SoftwareKeyboard::PasswordMode::Hide:
                swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_HIDE);
                break;
            case m3d::SoftwareKeyboard::PasswordMode::Delay:
                swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_HIDE_DELAY);
                break;
            default:
                swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_NONE);
        }

        swkbdSetFilterCallback(&swkbd, &m3d::SoftwareKeyboard::callback, NULL);
        SwkbdButton button = swkbdInputText(&swkbd, buffer, sizeof(buffer));

        m_lastText = buffer;

        switch (button) {
            case SWKBD_BUTTON_LEFT:
                m_lastButton = m3d::SoftwareKeyboard::Button::Left;
                break;
            case SWKBD_BUTTON_MIDDLE:
                m_lastButton = m3d::SoftwareKeyboard::Button::Middle;
                break;
            case SWKBD_BUTTON_RIGHT:
                m_lastButton = m3d::SoftwareKeyboard::Button::Right;
                break;
            default:
                m_lastButton = m3d::SoftwareKeyboard::Button::None;
        }
    }

    std::string SoftwareKeyboard::getLastInput() {
        return m_lastText;
    }

    m3d::SoftwareKeyboard::Button SoftwareKeyboard::getLastButton() {
        return m_lastButton;
    }

    SwkbdCallbackResult SoftwareKeyboard::callback(void* t_user, const char** t_ppMessage, const char* t_text, size_t t_textlen) {
        m3d::SoftwareKeyboard::KeyboardEvent evt(t_text);
        m3d::priv::input::keyboardValidator(evt);
        *t_ppMessage = evt.getMessage().c_str();
        printf("Result: %s\n", evt.getResult() == SWKBD_CALLBACK_OK ? "OK" : (evt.getResult() == SWKBD_CALLBACK_CONTINUE ? "Continue" : "Close"));
        return evt.getResult();
    }
} /* m3d */
