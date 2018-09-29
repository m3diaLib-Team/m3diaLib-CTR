#include <3ds.h>
#include <cstring>
#include "m3d/core/input.hpp"

namespace m3d {
    u32 Input::buttonsDown() {
        return hidKeysHeld();
    }
    
    u32 Input::buttonsPressed() {
        return hidKeysDown();
    }

    u32 Input::buttonsReleased() {
        return hidKeysUp();
    }

    bool Input::buttonPressed(Button t_button) {
        return (buttonsPressed() & t_button);
    }

    bool Input::buttonDown(Button t_button) {
        return (buttonsDown() & t_button);
    }

    bool Input::buttonReleased(Button t_button) {
        return (buttonsReleased() & t_button);
    }

    int Input::getCirclePadX() {
        circlePosition circle;
        hidCircleRead(&circle);
        return circle.dx;
    }

    int Input::getCirclePadY() {
        circlePosition circle;
        hidCircleRead(&circle);
        return circle.dy;
    }

    int Input::getTouchX() {
        touchPosition touch;
        hidTouchRead(&touch);
        return touch.px;
    }

    int Input::getTouchY() {
        touchPosition touch;
        hidTouchRead(&touch);
        return touch.py;
    }
}