#include <3ds.h>
#include <cstring>
#include "core/applet.hpp"

namespace m3d {
	Applet::Applet() :
	 					m_running(true) {
		aptInit();
		cfguInit();
		ptmuInit();
		acInit();
		romfsInit();
	}

	Applet::~Applet() {
		romfsExit();
		acExit();
		ptmuExit();
		cfguExit();
		aptExit();
	}

	bool Applet::isRunning() {
		hidScanInput(); // scan input since this gets called every frame
		return m_running;
	}

	void Applet::exit() {
		m_running = false;
	}

	void Applet::reboot() {
		APT_HardwareResetAsync();
	}

	void Applet::setSleepAllowed(bool t_allowed) {
		aptSetSleepAllowed(t_allowed);
	}

	bool Applet::getSleepAllowed() {
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

	bool Applet::launchLibApp(m3d::LibAppId t_id) {
		NS_APPID id;

		switch(t_id) {
			case LIBAPP_HOMEMENU:
				id = APPID_HOMEMENU;
				break;
			case LIBAPP_CAMERA:
				id = APPID_CAMERA;
				break;
			case LIBAPP_FRIENDS_LIST:
				id = APPID_FRIENDS_LIST;
				break;
			case LIBAPP_GAME_NOTES:
				id = APPID_GAME_NOTES;
				break;
			case LIBAPP_WEB:
				id = APPID_WEB;
				break;
			case LIBAPP_INSTRUCTION_MANUAL:
				id = APPID_INSTRUCTION_MANUAL;
				break;
			case LIBAPP_NOTIFICATIONS:
				id = APPID_NOTIFICATIONS;
				break;
			case LIBAPP_MIIVERSE:
				id = APPID_MIIVERSE;
				break;
			case LIBAPP_MIIVERSE_POSTING:
				id = APPID_MIIVERSE_POSTING;
				break;
			case LIBAPP_AMIIBO_SETTINGS:
				id = APPID_AMIIBO_SETTINGS;
				break;
			case LIBAPP_APPLICATION:
				id = APPID_APPLICATION;
				break;
			case LIBAPP_ESHOP:
				id = APPID_ESHOP;
				break;
			case LIBAPP_SOFTWARE_KEYBOARD:
				id = APPID_SOFTWARE_KEYBOARD;
				break;
			case LIBAPP_APPLETED:
				id = APPID_APPLETED;
				break;
			case LIBAPP_PNOTE_AP:
				id = APPID_PNOTE_AP;
				break;
			case LIBAPP_SNOTE_AP:
				id = APPID_SNOTE_AP;
				break;
			case LIBAPP_ERROR:
				id = APPID_ERROR;
				break;
			case LIBAPP_MINT:
				id = APPID_MINT;
				break;
			case LIBAPP_EXTRAPAD:
				id = APPID_EXTRAPAD;
				break;
			case LIBAPP_MEMOLIB:
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

	bool Applet::isNew3ds() {
		bool state;
		APT_CheckNew3DS(&state);
		return state;
	}

	bool Applet::is2ds() {
		u8 state;
		CFGU_GetModelNintendo2DS(&state);
		return (state == 0);
	}

	bool Applet::wifiConnected() {
		u32 state;
		ACU_GetWifiStatus(&state);
		return (state > 0);
	}

	m3d::ConsoleModel Applet::getConsoleModel() {
		u8 state;
		CFGU_GetSystemModel(&state);

		switch(state) {
			case 0:
				return MODEL_O3DS;
			case 1:
				return MODEL_O3DSXL;
			case 2:
				return MODEL_N3DS;
			case 3:
				return MODEL_2DS;
			case 4:
				return MODEL_N3DSXL;
			default:
				return MODEL_UNKNOWN;
		}
	}

	bool Applet::adapterPluggedIn() {
		bool state;
		PTMU_GetAdapterState(&state);
		return state;
	}

	bool Applet::isCharging() {
		u8 state;
		PTMU_GetBatteryChargeState(&state);
		return (state == 1);
	}

	int Applet::getBatteryLevel() {
		u8 state;
		PTMU_GetBatteryLevel(&state);
		return (state <= 5 && state >= 0 ? state : 0);
	}
} /* m3d */
