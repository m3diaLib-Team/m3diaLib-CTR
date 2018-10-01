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

#pragma once

namespace m3d {

    /**
     * @brief The MCU class, used for getting some low-level system information
     * @warning It is recommended to use functionality from the m3d::Applet-class instead of this class since the m3d::Applet-class is guarantueed to work even on non-CFW systems.
     */
    class MCU {
    public:
        enum class PowerLed {
            Normal,      ///< The normal mode of the led
            SleepMode,   ///< The led pulses slowly as it does in the sleep mode
            Off,         ///< Switch off power led
            Red,         ///< Red state of the led
            Blue,        ///< Blue state of the led
            BlinkingRed, ///< Blinking red state of power led and notification led
        }; // directly pulled from libctru

        /**
         * @brief Represents the firmware version
         */
        struct FWVersion {
            int high;
            int low;
        };

        /**
         * @brief Returns the voltage-level of the battery
         * @return The battery-voltage,
         */
        static int getBatteryVoltage();

        /**
         * @brief Returns the battery-level
         * @return The battery level
         */
        static int getBatteryLevel();

        /**
         * @brief Gets the sound-slider level
         * @return The level of the sound-slider
         */
        static int getSoundSliderLevel();

        /**
         * @brief Gets the 3D-slider level
         * @return The level of the 3D-slider
         */
        static int get3dSliderLevel();

        /**
         * @brief Gets the firmware version
         * @return The current firmware version
         */
        static m3d::MCU::FWVersion getFWVersion();

        /**
         * @brief Enables/disables the WiFi-LED
         * @param t_state Whether to enable or disable it
         */
        static void setWifiLed(bool t_state);

        /**
         * @brief Sets the state of the power-LED
         * @param t_state The state of the LED
         */
        static void setPowerLed(m3d::MCU::PowerLed t_state);
    };
}

#endif
