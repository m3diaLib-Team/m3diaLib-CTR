#include "core/error.hpp"

namespace m3d {
    Error::Error() :
        m_type(ERROR_TYPE_TEXT),
        m_errorCode(0),
        m_text(""),
        m_allowHomeButton(false),
        m_showErrorCode(false) { /* Do nothing */ }

    void Error::show() {
        errorType type;
        errorConf conf;

        switch(m_type) {
            case ERROR_TYPE_TEXT:
                type = ERROR_TEXT;
                break;
            case ERROR_TYPE_EULA:
                type = ERROR_EULA;
                break;
            case ERROR_TYPE_WORD_WRAP:
                type = ERROR_TEXT_WORD_WRAP;
                break;
            default:
                type = ERROR_TEXT;
        }

        errorInit(&conf, type, CFG_LANGUAGE_EN);
        errorText(&conf, m_text.c_str());

        conf.homeButton = m_allowHomeButton;

        if(m_showErrorCode) {
            errorCode(&conf, m_errorCode);
        }

        errorDisp(&conf);
    }

    void Error::setType(m3d::ErrorType t_type) {
        m_type = t_type;
    }

    m3d::ErrorType Error::getType() {
        return m_type;
    }

    void Error::setErrorCode(int t_code) {
        m_errorCode = t_code;
    }

    int Error::getErrorCode() {
        return m_errorCode;
    }

    void Error::setText(std::string t_text) {
        m_text = t_text.substr(0, 1899);
    }

    std::string Error::getText() {
        return m_text;
    }

    void Error::setAllowHomebutton(bool t_allowed) {
        m_allowHomeButton = t_allowed;
    }

    bool Error::getAllowHomeButton() {
        return m_allowHomeButton;
    }

    void Error::setShowErrorCode(bool t_show) {
        m_showErrorCode = t_show;
    }

    bool Error::getShowErrorCode() {
        return m_showErrorCode;
    }
} /* m3d */
