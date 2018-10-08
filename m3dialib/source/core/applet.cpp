#include <3ds.h>
#include <citro3d.h>
#include <cstring>
#include "m3d/core/applet.hpp"
#include "m3d/core/ledPattern.hpp"
#include "m3d/private/core.hpp"
#include "m3d/private/ndsp.hpp"

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
            gfxInitDefault();
            C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

            Result res;
            res = ndspInit();
            if (!res) {
                m3d::priv::ndsp::initialized = true;
            }

            srvInit();
            srvGetServiceHandle(&m3d::priv::core::ptmsysmHandle, "ptm:sysm");
            srvExit();

            if (isNew3ds()) {
                osSetSpeedupEnable(true);
            }
    }

    Applet::~Applet() {
        m3d::LEDPattern::stop();
        if (m3d::priv::ndsp::initialized) ndspExit();
        C3D_Fini();
        gfxExit();
        sdmcExit();
        romfsExit();
        acExit();
        ptmuExit();
        cfguExit();
        aptExit();
    }

    bool Applet::isRunning() {
        if (!aptMainLoop()) return false;

        hidScanInput(); // scan input since this gets called every frame
        C3D_FrameEnd(0);
        m_currentFrame++;
        return m_running;
    }

    void Applet::exit() {
        m_running = false;
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

        u32 aptbuf[0x400 / 4];

        memset(aptbuf, 0, sizeof(aptbuf));
        if (!aptLaunchLibraryApplet(id, aptbuf, sizeof(aptbuf), 0))
            return false;

        return true;
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

    int Applet::getCurrentFrame() {
        m_currentFrame = m_currentFrame % 60;
        return m_currentFrame;
    }
} /* m3d */
