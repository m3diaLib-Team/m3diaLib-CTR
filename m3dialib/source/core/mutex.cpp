#include "core/mutex.hpp"

namespace m3d {
    Mutex::Mutex() {
        RecursiveLock_Init(&m_mutex);
    }

    void Mutex::lock() {
        RecursiveLock_Lock(&m_mutex);
    }

    void Mutex::unlock() {
        RecursiveLock_Unlock(&m_mutex);
    }
} /* m3d */
