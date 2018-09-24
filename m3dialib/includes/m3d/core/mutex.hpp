/**
 * @file mutex.hpp
 * @brief Defines the Mutex class
 */
#ifndef MUTEX_H
#define MUTEX_H

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
         * @brief Destructor
         *
         * This automatically unlocks the mutex
         */
        ~Mutex();

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


#endif /* end of include guard: MUTEX_H */
