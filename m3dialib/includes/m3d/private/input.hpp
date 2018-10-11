#ifndef INPUT_PRIVATE_H
#define INPUT_PRIVATE_H

#pragma once
#include <3ds.h>
#include <functional>
#include "m3d/input/softwareKeyboard.hpp"

namespace m3d {
    namespace priv {
        namespace input {
            extern std::function<void(m3d::SoftwareKeyboard::KeyboardEvent&)> keyboardValidator;
        } /* input */
    } /* priv */
} /* m3d */


#endif /* end of include guard: INPUT_PRIVATE_H */
