/**
 * @file error.hpp
 * @brief Defines the Error class (used for displaying system error messages)
 */
#pragma once
#include <string>
#include <3ds.h>

namespace m3d {
	/**
	 * @brief Defines which type of error to display
	 */
	enum ErrorType {
		ERROR_TYPE_TEXT, 			///< Displays text passed to this applet
		ERROR_TYPE_EULA, 			///< Displays the EULA
		ERROR_TYPE_WORD_WRAP, ///< Displays the custom error message passed to this applet with automatic line wrapping
	};

	/**
	 * @brief The Error class, used for displaying error messages in the system-3ds style
	 */
	class Error {
	public:
		/**
		 * Initializes an Error object
		 */
		Error();

		/**
		 * Displays the error
		 */
		void show();

		/**
		 * Sets the error type
		 * @param t_type The error type to be set
		 */
		void setType(m3d::ErrorType t_type);

		/**
		 * Returns the error type
		 * @return The error type currently set
		 */
		m3d::ErrorType getType();

		/**
		 * Sets the error code
		 * @param t_code The error code to set
		 */
		void setErrorCode(int t_code);

		/**
		 * Returns the error code
		 * @return The error code currently set
		 */
		int getErrorCode();

		/**
		 * Sets the text to be displayed
		 * @param t_text The text to be set
		 */
		void setText(std::string t_text);

		/**
		 * Returns the text currently set to be displayed
		 * @return The current text
		 */
		std::string getText();

		/**
		 * Sets whether to allow the use of the home button
		 * @param t_allowed Whether the use of the home button is allowed or not
		 */
		void setAllowHomebutton(bool t_allowed);

		/**
		 * Returns whether the use of the home button is allowed
		 * @param t_allowed Whether the use of the home button is allowed or not
		 */
		bool getAllowHomeButton();

		/**
		 * Sets whether to show an error code
		 * @param t_show Whether show an error code or not
		 */
		void setShowErrorCode(bool t_show);

		/**
		 * Returns whether to show an error code
		 * @param t_allowed Whether show an error code or not
		 */
		bool getShowErrorCode();

	private:
		/* data */
		errorConf m_conf;
		m3d::ErrorType m_type;
		int m_errorCode;
		std::string m_text;
		bool m_allowHomeButton, m_showErrorCode;

	};
} /* m3d */
