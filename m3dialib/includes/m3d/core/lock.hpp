/**
 * @file lock.hpp
 * @brief Defines the Lock class
 */
#pragma once
#include <3ds.h>
#include "m3d/core/mutex.hpp"

namespace m3d {
    /**
     * @brief The Lock class used to lock mutexes
     */
    class Lock {
    public:
        /**
         * @brief Creates the lock
         * @param t_mutex The mutex to lock
         */
        Lock(m3d::Mutex& t_mutex);

        /**
         * @brief Destructs the lock
         * @note This automatically unlocks it's mutex
         */
        virtual ~Lock();

    private:
        /* data */
        m3d::Mutex m_mutex;
    };
} /* m3d */
