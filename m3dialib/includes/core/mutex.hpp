/**
 * @file mutex.hpp
 * @brief Defines the Mutex class
 */
#pragma once
#include <3ds.h>

namespace m3d {
    /**
     * @brief The mutex class
     */
    class Mutex {
    public:
        /**
         * @brief Creates the mutex
         */
        Mutex();

        /**
         * @brief Locks the mutex
         */
        void lock();

        /**
         * @brief Unlocks the mutex
         */
        void unlock();

    private:
        /* data */
        RecursiveLock m_mutex;
    };
} /* m3d */
