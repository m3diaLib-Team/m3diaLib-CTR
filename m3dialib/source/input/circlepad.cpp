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

        m3d::Vector2f getDirectionVector(bool t_useRadians) {
            circlePosition circle;
            hidCircleRead(&circle);

            float posX = (float) circle.dx / 155.f,
                  posY = (float) circle.dy / 155.f;

            m3d::Vector2f ret;
            if (posX == 0.f && posY > 0.f) {
                ret.u = 1.5708f * (t_useRadians ? 1 : (180.0/3.141592653589793238463));
            } else if (posX == 0.f && posY < 0.f) {
                ret.u = 4.71239f * (t_useRadians ? 1 : (180.0/3.141592653589793238463));
            } else if (posY == 0.f && posX > 0.f) {
                ret.u = 0.f;
            } else if (posY == 0.f && posX < 0.f) {
                ret.u = 3.14159f * (t_useRadians ? 1 : (180.0/3.141592653589793238463));
            } else if (posX == 0 && posY == 0) {
                ret.u = 0.f;
            } else {
                ret.u = atan(posY / posX) * (t_useRadians ? 1 : (180.0/3.141592653589793238463));
            }

            ret.v = sqrt((pow(posX, 2)) + (pow(posY, 2)));

            return ret;
        }
    } /* circle */
} /* m3d */
