#include "m3d/private/input.hpp"

namespace m3d {
    namespace priv {
        namespace input {
            std::function<void(m3d::SoftwareKeyboard::KeyboardEvent&)> keyboardValidator = [](m3d::SoftwareKeyboard::KeyboardEvent& evt){evt.valid();};
        } /* input */
    } /* priv */
} /* m3d */
