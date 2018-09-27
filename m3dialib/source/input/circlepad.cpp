#include <cmath>
#include "m3d/input/circlepad.hpp"

namespace m3d {
    namespace circlepad {
        int getXPosition() {
            circlePosition circle;
            hidCircleRead(&circle);

            return circle.dx;
        }

        int getYPosition() {
            circlePosition circle;
            hidCircleRead(&circle);

            return circle.dy;
        }
    } /* circle */
} /* m3d */
