#include "m3d/input/softwareKeyboard.hpp"

namespace m3d {
    SoftwareKeyboard::KeyboardEvent::KeyboardEvent(const std::string t_text) :
        m_text(t_text),
        m_message(""),
        m_callbackResult(SWKBD_CALLBACK_OK) { /* do nothing */ }

    void SoftwareKeyboard::KeyboardEvent::error(const std::string t_message) {
        m_message = t_message;
        m_callbackResult = SWKBD_CALLBACK_CONTINUE;
    }

    void SoftwareKeyboard::KeyboardEvent::close(const std::string t_message) {
        m_message = t_message;
        m_callbackResult = SWKBD_CALLBACK_CLOSE;
    }

    void SoftwareKeyboard::KeyboardEvent::valid() {
        m_message = "";
        m_callbackResult = SWKBD_CALLBACK_OK;
    }

    std::string SoftwareKeyboard::KeyboardEvent::getText() {
        return m_text;
    }

    SwkbdCallbackResult SoftwareKeyboard::KeyboardEvent::getResult() {
        return m_callbackResult;
    }

    std::string SoftwareKeyboard::KeyboardEvent::getMessage() {
        return m_message;
    }
} /* m3d */
