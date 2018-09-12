#include <3ds.h>
#include <cstring>
#include "m3d/core/applet.hpp"
#include "m3d/private/private.hpp"

namespace m3d {
    Applet::Applet() :
         m_running(true),
         m_currentFrame(0) {
            aptInit();
            cfguInit();
            ptmuInit();
            acInit();
            romfsInit();
            sdmcInit();

            Result res;
            res = ndspInit();
            if (!res) {
                m3d::priv::ndsp::initialized = true;
            }
    }

    Applet::~Applet() {
        ndspExit();
        sdmcExit();
        romfsExit();
        acExit();
        ptmuExit();
        cfguExit();
        aptExit();
    }

    bool Applet::isRunning() {
        hidScanInput(); // scan input since this gets called every frame
        m_currentFrame++;
        return m_running;
    }

    void Applet::exit() {
        m_running = false;
    }

    inline void Applet::reboot() {
        APT_HardwareResetAsync();
    }

    inline void Applet::setSleepAllowed(bool t_allowed) {
        aptSetSleepAllowed(t_allowed);
    }

    inline bool Applet::getSleepAllowed() {
        return aptIsSleepAllowed();
    }

    void Applet::launchSystemApp(u64 t_appId) {
        u8 param[0x300];
        u8 hmac[0x20];

        memset(param, 0, sizeof(param));
        memset(hmac, 0, sizeof(hmac));

        APT_PrepareToDoApplicationJump(0, t_appId, 0);
        APT_DoApplicationJump(param, sizeof(param), hmac);
    }

    bool Applet::launchLibApp(m3d::Applet::LibAppId t_id) {
        NS_APPID id;

        switch(t_id) {
            case m3d::Applet::LibAppId::HomeMenu:
                id = APPID_HOMEMENU;
                break;
            case m3d::Applet::LibAppId::Camera:
                id = APPID_CAMERA;
                break;
            case m3d::Applet::LibAppId::FriendsList:
                id = APPID_FRIENDS_LIST;
                break;
            case m3d::Applet::LibAppId::GameNotes:
                id = APPID_GAME_NOTES;
                break;
            case m3d::Applet::LibAppId::Web:
                id = APPID_WEB;
                break;
            case m3d::Applet::LibAppId::InstructionManual:
                id = APPID_INSTRUCTION_MANUAL;
                break;
            case m3d::Applet::LibAppId::Notifications:
                id = APPID_NOTIFICATIONS;
                break;
            case m3d::Applet::LibAppId::Miiverse:
                id = APPID_MIIVERSE;
                break;
            case m3d::Applet::LibAppId::MiiversePosting:
                id = APPID_MIIVERSE_POSTING;
                break;
            case m3d::Applet::LibAppId::AmiiboSettings:
                id = APPID_AMIIBO_SETTINGS;
                break;
            case m3d::Applet::LibAppId::EShopTiger:
                id = APPID_ESHOP;
                break;
            case m3d::Applet::LibAppId::SoftwareKeyboard:
                id = APPID_SOFTWARE_KEYBOARD;
                break;
            case m3d::Applet::LibAppId::MiiEditor:
                id = APPID_APPLETED;
                break;
            case m3d::Applet::LibAppId::PhotoSelector:
                id = APPID_PNOTE_AP;
                break;
            case m3d::Applet::LibAppId::SoundSelector:
                id = APPID_SNOTE_AP;
                break;
            case m3d::Applet::LibAppId::Error:
                id = APPID_ERROR;
                break;
            case m3d::Applet::LibAppId::EShopMint:
                id = APPID_MINT;
                break;
            case m3d::Applet::LibAppId::Extrapad:
                id = APPID_EXTRAPAD;
                break;
            case m3d::Applet::LibAppId::Memolib:
                id = APPID_MEMOLIB;
                break;
            default:
                id = APPID_NONE;
        }

        u32 aptbuf[0x400/4];

        memset(aptbuf, 0, sizeof(aptbuf));
        if (!aptLaunchLibraryApplet(id, aptbuf, sizeof(aptbuf), 0))
            return false;

        return true;
    }

    inline bool Applet::isNew3ds() {
        bool state;
        APT_CheckNew3DS(&state);
        return state;
    }

    inline bool Applet::is2ds() {
        u8 state;
        CFGU_GetModelNintendo2DS(&state);
        return (state == 0);
    }

    inline bool Applet::wifiConnected() {
        u32 state;
        ACU_GetWifiStatus(&state);
        return (state > 0);
    }

    m3d::Applet::ConsoleModel Applet::getConsoleModel() {
        u8 state;
        CFGU_GetSystemModel(&state);

        switch(state) {
            case 0:
                return m3d::Applet::ConsoleModel::Old3DS;
            case 1:
                return m3d::Applet::ConsoleModel::Old3DSXL;
            case 2:
                return m3d::Applet::ConsoleModel::New3DS;
            case 3:
                return m3d::Applet::ConsoleModel::Old2DS;
            case 4:
                return m3d::Applet::ConsoleModel::New3DSXL;
            default:
                return m3d::Applet::ConsoleModel::Unknown;
        }
    }

    inline bool Applet::adapterPluggedIn() {
        bool state;
        PTMU_GetAdapterState(&state);
        return state;
    }

    inline bool Applet::isCharging() {
        u8 state;
        PTMU_GetBatteryChargeState(&state);
        return (state == 1);
    }

    inline int Applet::getBatteryLevel() {
        u8 state;
        PTMU_GetBatteryLevel(&state);
        return (state <= 5 && state >= 0 ? state : 0);
    }

    int Applet::getCurrentFrame() {
        m_currentFrame = m_currentFrame % 60;
        return m_currentFrame;
    }
} /* m3d */
