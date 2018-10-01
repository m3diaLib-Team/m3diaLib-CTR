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

    m3d::MCU::FWVersion MCU::getFWVersion() {
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

    void MCU::setPowerLed(m3d::MCU::PowerLed t_state) {
        powerLedState f_state;

        switch(t_state) {
            case m3d::MCU::PowerLed::BlinkingRed:
                f_state = powerLedState::LED_BLINK_RED;
                break;
            case m3d::MCU::PowerLed::Blue:
                f_state = powerLedState::LED_BLUE;
                break;
            case m3d::MCU::PowerLed::Normal:
                f_state = powerLedState::LED_NORMAL;
                break;
            case m3d::MCU::PowerLed::Off:
                f_state = powerLedState::LED_OFF;
                break;
            case m3d::MCU::PowerLed::Red:
                f_state = powerLedState::LED_RED;
                break;
            case m3d::MCU::PowerLed::SleepMode:
                f_state = powerLedState::LED_SLEEP_MODE;
                break;
            default:
                f_state = powerLedState::LED_NORMAL;
                break;
        }

        MCUHWC_SetPowerLedState(f_state);
    }
}
