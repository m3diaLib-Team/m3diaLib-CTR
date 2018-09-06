#include "m3d/core/lock.hpp"

namespace m3d {
    Lock::Lock(m3d::Mutex& t_mutex) :
            m_mutex(t_mutex) {
        m_mutex.lock();
    }

    Lock::~Lock() {
        m_mutex.unlock();
    }
} /* m3d */
