#include <3ds.h>
#include <cstring>
#include "core/applet.hpp"

namespace m3d {
	Applet::Applet() {
		aptInit();
		cfguInit();
		ptmuInit();
	}

	Applet::~Applet() {
		ptmuExit();
		cfguExit();
		aptExit();
	}

	bool Applet::isRunning() {
		return aptMainLoop();
	}

	void Applet::exit() {
		aptExit();
		APT_CloseApplication(nullptr, 0, 0);
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

	bool Applet::getNew3ds() {
		bool state;
		APT_CheckNew3DS(&state);
		return state;
	}
} /* m3d */
