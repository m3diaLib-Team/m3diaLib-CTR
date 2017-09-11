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
		REGION_JPN = 0, ///< Japan
		REGION_USA = 1, ///< USA
		REGION_EUR = 2, ///< Europe
		REGION_AUS = 3, ///< Australia
		REGION_CHN = 4, ///< China
		REGION_KOR = 5, ///< Korea
		REGION_TWN = 6 	///< Taiwan
	};

	/**
	 * @brief Language values
	 */
	enum Language {
		LANGUAGE_JP = 0, 	///< Japanese
		LANGUAGE_EN = 1, 	///< English
		LANGUAGE_FR = 2, 	///< French
		LANGUAGE_DE = 3, 	///< German
		LANGUAGE_IT = 4, 	///< Italian
		LANGUAGE_ES = 5, 	///< Spanish
		LANGUAGE_ZH = 6, 	///< Simplified chinese
		LANGUAGE_KO = 7, 	///< Korean
		LANGUAGE_NL = 8, 	///< Dutch
		LANGUAGE_PT = 9, 	///< Portugese
		LANGUAGE_RU = 10, ///< Russian
		LANGUAGE_TW = 11 	///< Traditional chinese
	};

	/**
	 * @brief Defines ids of LibApps
	 */
	enum LibAppId {
		APPID_NONE 								= 0,
		APPID_HOMEMENU 						= 0x101, ///< Home menu
		APPID_CAMERA 							= 0x110, ///< Camera applet
		APPID_FRIENDS_LIST 				= 0x112, ///< Friends list applet
		APPID_GAME_NOTES 					= 0x113, ///< Game notes applet
		APPID_WEB 								= 0x114, ///< Internet browser
		APPID_INSTRUCTION_MANUAL 	= 0x115, ///< Instruction manual applet
		APPID_NOTIFICATIONS 			= 0x116, ///< Notifications applet
		APPID_MIIVERSE 						= 0x117, ///< Miiverse applet
		APPID_MIIVERSE_POSTING 		= 0x118, ///< Miiverse posting applet
		APPID_AMIIBO_SETTINGS 		= 0x119, ///< Amiibo settings applet
		APPID_APPLICATION 				= 0x300, ///< Application (?)
		APPID_ESHOP 							= 0x301, ///< eShop (tiger)
		APPID_SOFTWARE_KEYBOARD 	= 0x401, ///< Software keyboard (do not use, use the m3d::SoftwareKeyboard class instead)
		APPID_APPLETED 						= 0x402, ///< AppletEd (Mii editor)
		APPID_PNOTE_AP 						= 0x404, ///< Photo selector
		APPID_SNOTE_AP 						= 0x405, ///< Sound selector
		APPID_ERROR 							= 0x406, ///< Error (do not use, use the m3d::Error class instead)
		APPID_MINT 								= 0x407, ///< Mint (eShop)
		APPID_EXTRAPAD 						= 0x408, ///< Extrapad
		APPID_MEMOLIB 						= 0x409  ///< Memolib
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
		 * @brief Returns if the applet is still running
		 */
		bool isRunning();

		/**
		 * @brief Exits the applet
		 */
		void exit();

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
		bool launchSystemApp(u64 t_appId);

		/**
		 * @brief Launches a library app (extrapad, memolib, ...)
		 * @param  t_id The id of the app
		 * @return      The success state of the launch
		 */
		bool launchLibApp(m3d::LibAppId t_id);

	private:
		/* data */
		bool m_sleepAllowed;

	};
} /* m3d */
