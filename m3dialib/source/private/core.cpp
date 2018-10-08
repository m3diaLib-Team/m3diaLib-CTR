#include "m3d/private/core.hpp"

namespace m3d {
    namespace priv {
        namespace core {
            std::atomic<bool> ledPatternRunning(false), consoleTop(false), consoleBottom(false);
            bool socuInitialized = false, curlInitialized = false;
            Handle ptmsysmHandle = 0;
            u32* socubuf = nullptr;
        } /* core */
    } /* priv */
} /* m3d */
