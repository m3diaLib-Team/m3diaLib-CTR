#include <3ds.h>
#include "core/applet.hpp"

namespace m3d {
	Applet::Applet() {
		// Do nothing
	}

	bool Applet::isRunning() {
		return aptMainLoop();
	}

	void Applet::exit() {
		// aptSendCommand(APTCMD_EXIT);
		APT_CloseApplication(0, 0, 0);
	}
} /* m3d */
