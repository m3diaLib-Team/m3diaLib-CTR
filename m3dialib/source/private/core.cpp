#include "m3d/private/core.hpp"

namespace m3d {
    namespace priv {
        namespace core {
            bool socuInitialized = false;
            std::atomic<bool> ledPatternRunning(false);
            Handle ptmsysmHandle = 0;
            u32* socubuf = nullptr;
        } /* core */
    } /* priv */
} /* m3d */
