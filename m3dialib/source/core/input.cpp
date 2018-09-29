#include <3ds.h>
#include <cstring>
#include "m3d/core/input.hpp"
#include "m3d/input/buttons.hpp"

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

    bool Input::buttonPressed(m3d::buttons::Button t_button) {
        return (buttonsPressed() & t_button);
    }

    bool Input::buttonDown(m3d::buttons::Button t_button) {
        return (buttonsDown() & t_button);
    }

    bool Input::buttonReleased(m3d::buttons::Button t_button) {
        return (buttonsReleased() & t_button);
    }
}