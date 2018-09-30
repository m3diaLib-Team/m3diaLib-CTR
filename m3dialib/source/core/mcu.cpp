#include <3ds.h>

#include "m3d/core/mcu.hpp"
#include "m3d/core/applet.hpp"

namespace m3d {
    int MCU::getBatteryVoltage() {
        u8 *voltage = 0;
        MCUHWC_GetBatteryVoltage(voltage);
        return *voltage;
    }

    int MCU::getBatteryLevel() {
        u8 *level = 0;
        MCUHWC_GetBatteryLevel(level);
        return *level;
    }

    int MCU::getSoundSliderLevel() {
        u8 *level = 0;
        MCUHWC_GetSoundSliderLevel(level);
        return *level;
    }

    int MCU::get3dSliderLevel() {
        if (m3d::Applet::getConsoleModel() == m3d::Applet::ConsoleModel::Old2DS ||
        m3d::Applet::getConsoleModel() == m3d::Applet::ConsoleModel::Unknown) {
            return 0;
        } else {
            u8 *level = 0;
            MCUHWC_Get3dSliderLevel(level);
            return *level;
        }
    }

    FWVersion MCU::getFWVersion() {
        u8 *high = 0;
        u8 *low = 0;
        FWVersion fw;
        MCUHWC_GetFwVerHigh(high);
        MCUHWC_GetFwVerLow(low);
        fw.high = *high;
        fw.low = *low;
        return fw;
    }

    void MCU::setWifiLed(bool t_state) {
        MCUHWC_SetWifiLedState(t_state);
    }

    void MCU::setPowerLed(powerLed t_state) {
        powerLedState f_state;
        switch(t_state) {
            case powerLed::LED_BLINK_RED:
                f_state = powerLedState::LED_BLINK_RED;
                break;
            case powerLed::LED_BLUE:
                f_state = powerLedState::LED_BLUE;
                break;
            case powerLed::LED_NORMAL:
                f_state = powerLedState::LED_NORMAL;
                break;
            case powerLed::LED_OFF:
                f_state = powerLedState::LED_OFF;
                break;
            case powerLed::LED_RED:
                f_state = powerLedState::LED_RED;
                break;
            case powerLed::LED_SLEEP_MODE:
                f_state = powerLedState::LED_SLEEP_MODE;
                break;
            default:
                f_state = powerLedState::LED_NORMAL;
                break;
        }
        MCUHWC_SetPowerLedState(f_state);
    }
}