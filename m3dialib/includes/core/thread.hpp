/**
 * @file thread.hpp
 * @brief Defines the Thread class
 */
#pragma once
#include <3ds.h>
#include <string>
#include "./threadParameter.hpp"

using CTRU_Thread = Thread;

namespace m3d {
    class Thread {
    public:
        /**
         * @brief Defines different predefined priority levels of a thread
         */
        enum class Priority {
            Highest  = 39, ///< Highest possible priority
            VeryHigh = 35, ///< Very high priority
            High     = 28, ///< High priority
            Normal   = 20, ///< Normal priority (one higher than main thread)
            Low      = 13, ///< Low priority
            VeryLow  = 5, ///< Very low priority
            Lowest   = 0, ///< Lowest possible priority
            Default          ///< One lower than current thread
        };

        /**
         * @brief Initzializes the thread
         * @param t_function  The thread function
         * @param t_parameter The parameter to pass to the function
         * @param t_priority  The priority of the thread
         * @param t_autostart Whether the thread should start instantly
         * @param t_detached  Whether the thread starts detached or not
         * @param t_stackSize The stacksize allocated for the thread in bytes (rounded to multiples of 8 bytes)
         * @note t_function needs to be of type `void` and take one (and only one) parameter of type m3d::ThreadParmater
         * @warning If the thread priority is lower than the priority of the calling thread, the thread will never get executed. Use m3d::Thread::getCurrentPriority() to get the priority of the current thread
         */
        Thread(void t_function(m3d::ThreadParameter), m3d::ThreadParameter t_parameter = nullptr, m3d::Thread::Priority t_priority = m3d::Thread::Priority::Default, bool t_autostart = false, bool t_detached = false, unsigned long long int t_stackSize = 4 * 1024);

        /**
         * @brief Initzializes the thread with a specific priority
         * @param t_function  The thread function
         * @param t_priority  The priority of the thread (Ranging from 0 to 39)
         * @param t_parameter The parameter to pass to the function
         * @param t_autostart Whether the thread should start instantly
         * @param t_detached  Whether the thread starts detached or not
         * @param t_stackSize The stacksize allocated for the thread in bytes (rounded to multiples of 8 bytes)
         * @note t_function needs to be of type `void` and take one (and only one) parameter of type m3d::ThreadParmater
         * @note Higher priority values mean a higher priority
         * @warning If the priority exceeds this range, it will be clamped
         * @warning If the thread priority is higher or equal than the priority of the calling thread, calling thread will get paused. Use m3d::Thread::getCurrentPriority() to get the priority of the current thread
         */
        Thread(void t_function(m3d::ThreadParameter), int t_priority, m3d::ThreadParameter t_parameter = nullptr, bool t_autostart = false, bool t_detached = false, unsigned long long int t_stackSize = 4 * 1024);

        /**
         * @brief Sets the size of the stack that gets allocated for the next thread that get's started
         * @param t_stackSize The allocated space in bytes (rounded to multiples of 8 bytes)
         */
        void setStackSize(unsigned long long int t_stackSize);

        /**
         * @brief Destructs the thread
         */
        virtual ~Thread();

        /**
         * @brief Starts the thread
         * @param t_detached Whether the thread should start detached or not
         */
        void start(bool t_detached = false);

        /**
         * @brief Detaches the thread
         *
         * After a thread is detatched, the Thread-object can be used to create a new thread.
         */
        void detach();

        /**
         * @brief Waits for the thread to finish
         * @param t_timeout The timeout in nanoseconds. Leave it for no timeout
         * @return The exit code of the thread (-1 if the thread wasn't started)
         */
        int join(long long unsigned int t_timeout = U64_MAX);

        /**
         * @brief Returns the exit code of the finished thread function
         * @return The exit code
         */
        int getExitCode();

        /**
         * @brief Returns the priority of the calling thread
         * @return The priority of the thread
         */
        static int getCurrentPriority();

    private:
        struct ThreadData {
            m3d::ThreadParameter m_parameter;
            void (*m_function)(m3d::ThreadParameter t_param);
        };

        static void threadFunction(void* t_arg);

        /* data */
        int m_priority, m_stackSize;
        bool m_running, m_started;
        m3d::Thread::ThreadData m_data;
        CTRU_Thread m_thread;
    };
} /* m3d */
