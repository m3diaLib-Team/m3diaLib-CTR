/**
 * @file error.hpp
 * @brief Defines the Error class (used for displaying system error messages)
 */
#ifndef ERROR_H
#define ERROR_H

#pragma once
#include <string>
#include <3ds.h>

namespace m3d {
    /**
     * @brief The Error class, used for displaying error messages in the system-3ds style
     */
    class Error {
    public:
        /**
         * @brief Defines which type of error to display
         */
        enum class ErrorType {
            Text,      ///< Displays text passed to this applet
            Eula,      ///< Displays the EULA
            WordWrap  ///< Displays the custom error message passed to this applet with automatic line wrapping
        };

        /**
         * @brief Initializes an Error object
         */
        Error();

        /**
         * @brief Displays the error
         */
        void show();

        /**
         * @brief Sets the error type
         * @param t_type The error type to be set
         */
        void setType(m3d::Error::ErrorType t_type);

        /**
         * @brief Returns the error type
         * @return The error type currently set
         */
        m3d::Error::ErrorType getType();

        /**
         * @brief Sets the error code
         * @param t_code The error code to set
         */
        void setErrorCode(int t_code);

        /**
         * @brief Returns the error code
         * @return The error code currently set
         */
        int getErrorCode();

        /**
         * @brief Sets the text to be displayed
         * @param t_text The text to be set
         */
        void setText(std::string t_text);

        /**
         * @brief Returns the text currently set to be displayed
         * @return The current text
         */
        std::string getText();

        /**
         * @brief Sets whether to allow the use of the home button
         * @param t_allowed Whether the use of the home button is allowed or not
         */
        void setAllowHomebutton(bool t_allowed);

        /**
         * @brief Returns whether the use of the home button is allowed
         * @return Whether the use of the home button is allowed or not
         */
        bool getAllowHomeButton();

        /**
         * @brief Sets whether to show an error code
         * @param t_show Whether to show an error code or not
         */
        void setShowErrorCode(bool t_show);

        /**
         * @brief Returns whether to show an error code
         * @return Whether to show an error code or not
         */
        bool getShowErrorCode();

    private:
        /* data */
        errorConf m_conf;
        m3d::Error::ErrorType m_type;
        int m_errorCode;
        std::string m_text;
        bool m_allowHomeButton, m_showErrorCode;

    };
} /* m3d */


#endif /* end of include guard: ERROR_H */
