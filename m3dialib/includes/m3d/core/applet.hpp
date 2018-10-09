/**
 * @file applet.hpp
 * @brief Defines the applet class (used for running the app)
 */
#ifndef APPLET_H
#define APPLET_H

/**
 * @brief The general m3d-namespace
 */
namespace m3d {
   /**
    * @brief The applet class (used for running the app)
    */
   class Applet {
   public:
       /**
        * @brief Region values
        */
       enum class Region {
           Japan,     ///< Japan
           Usa,       ///< USA
           Europe,    ///< Europe
           Australia, ///< Australia
           China,     ///< China
           Korea,     ///< Korea
           Taiwan     ///< Taiwan
       };

       /**
        * @brief Language values
        */
       enum class Language {
           Japanese,          ///< Japanese
           English,           ///< English
           French,            ///< French
           German,            ///< German
           Italian,           ///< Italian
           Spanish,           ///< Spanish
           ChineseSimplified, ///< Simplified chinese
           Korean,            ///< Korean
           Dutch,             ///< Dutch
           Portugese,         ///< Portugese
           Russian,           ///< Russian
           ChineseTraditional ///< Traditional chinese
       };

       /**
        * @brief Defines ids of LibApps
        */
       enum class LibAppId {
           None,
           HomeMenu,              ///< Home menu
           Camera,                ///< Camera applet
           FriendsList,           ///< Friends list applet
           GameNotes,             ///< Game notes applet
           Web,                   ///< Internet browser
           InstructionManual,     ///< Instruction manual applet
           Notifications,         ///< Notifications applet
           Miiverse,              ///< Miiverse applet
           MiiversePosting,       ///< Miiverse posting applet
           AmiiboSettings,        ///< Amiibo settings applet
           EShopTiger,            ///< eShop (tiger)
           SoftwareKeyboard,      ///< Software keyboard (do not use, use the m3d::SoftwareKeyboard class instead)
           MiiEditor,             ///< AppletEd (Mii editor)
           PhotoSelector,         ///< Photo selector
           SoundSelector,         ///< Sound selector
           Error,                 ///< Error (do not use, use the m3d::Error class instead)
           EShopMint,             ///< Mint (eShop)
           Extrapad,              ///< Extrapad
           Memolib                ///< Memolib
       };

       /**
        * @brief Defines the different 3DS models
        */
       enum class ConsoleModel {
           Old3DS,     ///< Old 3DS
           Old3DSXL,   ///< Old 3DS XL
           New3DS,     ///< New 3DS
           New3DSXL,   ///< New 3DS XL
           Old2DS,     ///< 2DS
           Unknown
       };

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
       static inline void reboot() {
           APT_HardwareResetAsync();
       }

       /**
        * @brief Sets whether stand-by mode is allowed
        * @param t_allowed Stand-by mode allowed?
        */
       static inline void setSleepAllowed(bool t_allowed) {
           aptSetSleepAllowed(t_allowed);
       }

       /**
        * @brief Gets whether stand-by mode is allowed
        * @return Stand-by mode allowed?
        */
       static inline bool getSleepAllowed() {
           return aptIsSleepAllowed();
       }

       /**
        * @brief Gets the 3D slider state on 3DS systems
        * @return 3D slider state
        */
       static inline float get3dSliderState() {
           if (getConsoleModel() != ConsoleModel::Old2DS || getConsoleModel() != ConsoleModel::Unknown) {
               return osGet3DSliderState();
           } else {
               return 0.0;
           }
       }

       /**
        * @brief Launches a system app
        * @param  t_appId The app id of the
        * @return         The success state of the launch
        *
        * To get the id of the app you want to launch, please refer to <a href="http://3dbrew.org/wiki/Title_list#00040010_-_System_Applications" target="_blank">http://3dbrew.org/wiki/Title_list#00040010_-_System_Applications</a>.
        */
       static void launchSystemApp(u64 t_appId);

       /**
        * @brief Launches a library app (extrapad, memolib, ...)
        * @param  t_id The id of the app
        * @return      The success state of the launch
        */
       static bool launchLibApp(m3d::Applet::LibAppId t_id);

       /**
        * @brief Returns whether the system is a New3DS
        * @return Whether the system is a New3DS or not
        */
       static inline bool isNew3ds() {
           bool state;
           APT_CheckNew3DS(&state);
           return (state == 0);
       }

       /**
        * @brief Returns whether the system is a 2DS
        * @return Whether the system is a 2DS or not
        */
       static inline bool is2ds() {
           u8 state;
           CFGU_GetModelNintendo2DS(&state);
           return (state == 0);
       }

       /**
        * @brief Returns the model of the system
        * @return The system model
        */
       static m3d::Applet::ConsoleModel getConsoleModel();

       /**
        * @brief Returns whether the system is connected to a wifi network
        * @return The state of whether the system is connected to a wifi network or not
        */
       static inline bool wifiConnected() {
           u32 state;
           ACU_GetWifiStatus(&state);
           return (state > 0);
       }

       /**
        * @brief Returns whether the power adapter is plugged in
        * @return The state whether the power adapter is plugged in or not
        */
       static inline bool adapterPluggedIn() {
           bool state;
           PTMU_GetAdapterState(&state);
           return state;
       }

       /**
        * @brief Returns whether the system is charging or not
        * @return The charging state of the console
        */
       static inline bool isCharging() {
           u8 state;
           PTMU_GetBatteryChargeState(&state);
           return (state == 1);
       }

       /**
        * @brief Returns the current battery level of the console
        * @return The battery level of the console (0-5)
        */
       static inline int getBatteryLevel() {
           u8 state;
           PTMU_GetBatteryLevel(&state);
           return (state <= 5 && state >= 0 ? state : 0);
       }

       /**
        * @brief Returns the current sound volume of the console
        * @return The sound slider level (0-63)
        */
       static inline int getSoundVolume() {
           u8 state;
           HIDUSER_GetSoundVolume(&state);
           return (state || 5);
       }

       /**
        * @brief Returns the current frame
        * @return The currently drawn frame (ranging from 0 to 59)
        */
       int getCurrentFrame();

       /**
        * @brief Whether to enable the New 3DS speedup or not
        * @param t_enable Whether or not to enable the speedup
        * @note By default, the speedup is enabled on New 3DS consoles
        */
       static inline void enableSpeedup(bool t_enable) {
           osSetSpeedupEnable(t_enable);
       }

   private:
       /* data */
       bool m_sleepAllowed, m_running;
       int m_currentFrame;

   };
} /* m3d */


#endif /* end of include guard: APPLET_H */
