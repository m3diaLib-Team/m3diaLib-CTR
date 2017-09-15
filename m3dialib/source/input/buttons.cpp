#include "input/buttons.hpp"

namespace m3d {
	namespace buttons {
		bool buttonPressed(m3d::buttons::Button t_button) {
			return (hidKeysDown() & t_button);
		}

		bool buttonDown(m3d::buttons::Button t_button) {
			return (hidKeysHeld() & t_button);
		}

		bool buttonReleased(m3d::buttons::Button t_button) {
			return (hidKeysUp() & t_button);
		}
	} /* buttons */
} /* m3d */
