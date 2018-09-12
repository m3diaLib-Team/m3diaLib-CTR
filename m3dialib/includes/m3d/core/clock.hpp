/**
 * @file clock.hpp
 * @brief Defines the Clock class
 */
#ifndef CLOCK_H
#define CLOCK_H

#pragma once
#include <3ds.h>
#include "lock.hpp"
#include "thread.hpp"
#include "time.hpp"

namespace m3d {
    /**
     * @brief The clock class
     */
    class Clock {
    public:
        /**
         * @brief Initializes the clock
         */
        Clock();

        /**
         * @brief Destructs the clock
         */
        ~Clock();

        /**
         * @brief Sets the time of the clock in milliseconds
         * @param t_time The time-object
         */
        void setTime(unsigned long long int t_milliseconds);

        /**
         * @brief Sets the time of the clock
         * @param t_time The time-object
         */
        void setTime(m3d::Time t_time);

        /**
         * @brief Starts the clock
         */
        void start();

        /**
         * @brief Starts the clock in countdown-mode
         */
        void countdown();

        /**
         * @brief Stops the clock
         */
        void stop();

        /**
         * @brief Pauses the clock (stops it but preserved time)
         */
        void pause();

        /**
         * @brief Resets the clock
         */
        void reset();

        /**
         * @brief Returns the time of the clock
         * @return The time-object
         */
        m3d::Time& getTime();

    private:
        void runningThread(m3d::Parameter);

        /* data */
        bool m_started;
        unsigned long long int m_lastCheck;
        std::atomic<bool> m_running, m_reverse;
        m3d::Time m_time;
        m3d::Mutex m_mutex;
        m3d::Thread m_thread;
    };
} /* m3d */


#endif /* end of include guard: CLOCK_H */
