#include "m3d/input/touch.hpp"

namespace m3d {
    namespace touch {
        int getXPosition() {
            touchPosition touch;
            hidTouchRead(&touch);

            return touch.px;
        }

        int getYPosition() {
            touchPosition touch;
            hidTouchRead(&touch);

            return touch.py;
        }
    } /* touch */
} /* m3d */
