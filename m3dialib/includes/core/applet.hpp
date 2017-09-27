/**
 * @file applet.hpp
 * @brief Defines the applet class (used for running the app)
 */

 /**
  * @brief The general m3d-namespace
  */
namespace m3d {
	/**
	 * @brief Region values
	 */
	enum Region {
		REGION_JPN, ///< Japan
		REGION_USA, ///< USA
		REGION_EUR, ///< Europe
		REGION_AUS, ///< Australia
		REGION_CHN, ///< China
		REGION_KOR, ///< Korea
		REGION_TWN 	///< Taiwan
	};

	/**
	 * @brief Language values
	 */
	enum Language {
		LANGUAGE_JP, 	///< Japanese
		LANGUAGE_EN, 	///< English
		LANGUAGE_FR, 	///< French
		LANGUAGE_DE, 	///< German
		LANGUAGE_IT, 	///< Italian
		LANGUAGE_ES, 	///< Spanish
		LANGUAGE_ZH, 	///< Simplified chinese
		LANGUAGE_KO, 	///< Korean
		LANGUAGE_NL, 	///< Dutch
		LANGUAGE_PT, 	///< Portugese
		LANGUAGE_RU,	///< Russian
		LANGUAGE_TW 	///< Traditional chinese
	};

	/**
	 * @brief Defines ids of LibApps
	 */
	enum LibAppId {
		LIBAPP_NONE,
		LIBAPP_HOMEMENU,              ///< Home menu
		LIBAPP_CAMERA,                ///< Camera applet
		LIBAPP_FRIENDS_LIST,          ///< Friends list applet
		LIBAPP_GAME_NOTES,            ///< Game notes applet
		LIBAPP_WEB,                   ///< Internet browser
		LIBAPP_INSTRUCTION_MANUAL,    ///< Instruction manual applet
		LIBAPP_NOTIFICATIONS,         ///< Notifications applet
		LIBAPP_MIIVERSE,              ///< Miiverse applet
		LIBAPP_MIIVERSE_POSTING,      ///< Miiverse posting applet
		LIBAPP_AMIIBO_SETTINGS,       ///< Amiibo settings applet
		LIBAPP_APPLICATION,           ///< Application (?)
		LIBAPP_ESHOP,                 ///< eShop (tiger)
		LIBAPP_SOFTWARE_KEYBOARD,     ///< Software keyboard (do not use, use the m3d::SoftwareKeyboard class instead)
		LIBAPP_APPLETED,              ///< AppletEd (Mii editor)
		LIBAPP_PNOTE_AP,              ///< Photo selector
		LIBAPP_SNOTE_AP,              ///< Sound selector
		LIBAPP_ERROR,                 ///< Error (do not use, use the m3d::Error class instead)
		LIBAPP_MINT,                  ///< Mint (eShop)
		LIBAPP_EXTRAPAD,              ///< Extrapad
		LIBAPP_MEMOLIB                ///< Memolib
	};

	/**
	 * @brief Defines the different 3DS models
	 */
	enum ConsoleModel {
		MODEL_O3DS,     ///< Old 3DS
		MODEL_O3DSXL,   ///< Old 3DS XL
		MODEL_N3DS,     ///< New 3DS
		MODEL_N3DSXL,   ///< New 3DS XL
		MODEL_2DS,      ///< 2DS
		MODEL_UNKNOWN
	};

	/**
	 * @brief The applet class (used for running the app)
	 */
	class Applet {
	public:
		/**
		 * @brief Creates the applet
		 */
		Applet();

		/**
		 * @brief Destructs the applet
		 */
		~Applet();

		/**
		 * @brief Returns if the applet is still running
		 */
		bool isRunning();

		/**
		 * @brief Exits the applet
		 */
		void exit();

		/**
		 * @brief Reboots the system
		 */
		void reboot();

		/**
		 * @brief Sets whether stand-by mode is allowed
		 * @param t_allowed Stand-by mode allowed?
		 */
		void setSleepAllowed(bool t_allowed);

		/**
		 * @brief Gets whether stand-by mode is allowed
		 * @return Stand-by mode allowed?
		 */
		bool getSleepAllowed();

		/**
		 * @brief Launches a system app
		 * @param  t_appId The app id of the
		 * @return         The success state of the launch
		 *
		 * To get the id of the app you want to launch, please refer to <a href="http://3dbrew.org/wiki/Title_list#00040010_-_System_Applications" target="_blank">http://3dbrew.org/wiki/Title_list#00040010_-_System_Applications</a>.
		 */
		void launchSystemApp(u64 t_appId);

		/**
		 * @brief Launches a library app (extrapad, memolib, ...)
		 * @param  t_id The id of the app
		 * @return      The success state of the launch
		 */
		bool launchLibApp(m3d::LibAppId t_id);

		/**
		 * @brief Returns whether the system is a New3DS
		 * @return Whether the system is a New3DS or not
		 */
		bool isNew3ds();

		/**
		 * @brief Returns whether the system is a 2DS
		 * @return Whether the system is a 2DS or not
		 */
		bool is2ds();

		/**
		 * @brief Returns the model of the system
		 * @return The system model
		 */
		m3d::ConsoleModel getConsoleModel();

		/**
		 * @brief Returns whether the system is connected to a wifi network
		 * @return The state of whether the system is connected to a wifi network or not
		 */
		bool wifiConnected();

		/**
		 * @brief Returns whether the power adapter is plugged in
		 * @return The state whether the power adapter is plugged in or not
		 */
		bool adapterPluggedIn();

		/**
		 * @brief Returns whether the system is charging or not
		 * @return The charging state of the console
		 */
		bool isCharging();

		/**
		 * @brief Returns the current battery level of the console
		 * @return The battery level of the console (0-5)
		 */
		int getBatteryLevel();

	private:
		/* data */
		bool m_sleepAllowed, m_running;

	};
} /* m3d */
