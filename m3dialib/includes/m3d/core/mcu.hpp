///////////////////////////////////////
//     mcu.hpp - MCU functions       //
// Ported from DKP by bennyman123abc //
///////////////////////////////////////

/**
 * @file mcu.hpp
 * @brief Defines the mcu class (used for getting some low-level system information)
 */
#ifndef MCU_H
#define MCU_H

namespace m3d {    
    enum powerLed {
        LED_NORMAL = 1,	///< The normal mode of the led
        LED_SLEEP_MODE,	///< The led pulses slowly as it does in the sleep mode
        LED_OFF, 	///< Switch off power led
        LED_RED,	///< Red state of the led
        LED_BLUE,	///< Blue state of the led
        LED_BLINK_RED,	///< Blinking red state of power led and notification led
    }; // directly pulled from libctru

    struct FWVersion {
        int high;
        int low;
    };

    class MCU {
    public:
        static int getBatteryVoltage();
        static int getBatteryLevel();
        static int getSoundSliderLevel();
        static int get3dSliderLevel();
        static FWVersion getFWVersion();
        static void setWifiLed(bool t_state);
        static void setPowerLed(powerLed t_state);
    };
}

#endif