/**
 * @file thread.hpp
 * @brief Defines the Thread class
 */
#pragma once
#include <3ds.h>
#include <functional>
#include <string>
#include "./parameter.hpp"

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
            VeryLow  = 5,  ///< Very low priority
            Lowest   = 0,  ///< Lowest possible priority
            Default        ///< One lower than current thread
        };

        /**
         * @brief Constructs the thread
         * @param t_function  The thread function
         * @param t_parameter The parameter to pass to the function
         * @param t_priority  The priority of the thread
         * @param t_autostart Whether the thread should start instantly
         * @param t_detached  Whether the thread starts detached or not
         * @param t_stackSize The stacksize allocated for the thread in bytes (rounded to multiples of 8 bytes)
         * @note t_function needs to be of type `void` and take one (and only one) parameter of type m3d::Parameter
         * @warning If the thread priority is lower than the priority of the calling thread, the thread will never get executed. Use m3d::Thread::getCurrentPriority() to get the priority of the current thread
         */
        Thread(std::function<void(m3d::Parameter)> t_function, m3d::Parameter t_parameter = nullptr, m3d::Thread::Priority t_priority = m3d::Thread::Priority::Default, bool t_autostart = false, bool t_detached = false, unsigned long long int t_stackSize = 4 * 1024);

        /**
         * @brief Constructs the thread with a specific priority
         * @param t_function  The thread function
         * @param t_parameter The parameter to pass to the function
         * @param t_priority  The priority of the thread (Ranging from 0 to 39)
         * @param t_autostart Whether the thread should start instantly
         * @param t_detached  Whether the thread starts detached or not
         * @param t_stackSize The stacksize allocated for the thread in bytes (rounded to multiples of 8 bytes)
         * @note t_function needs to be of type `void` and take one (and only one) parameter of type m3d::Parameter
         * @note Higher priority values mean a higher priority
         * @warning If the priority exceeds this range, it will be clamped
         * @warning If the thread priority is higher or equal than the priority of the calling thread, calling thread will get paused. Use m3d::Thread::getCurrentPriority() to get the priority of the current thread
         */
        Thread(std::function<void(m3d::Parameter)> t_function, m3d::Parameter t_parameter, int t_priority, bool t_autostart = false, bool t_detached = false, unsigned long long int t_stackSize = 4 * 1024);

        /**
         * @brief Destructs the thread
         */
        virtual ~Thread();

        /**
         * @brief Sets the priority for the next thread that get's started
         * @param t_priority The priority of the thread
         * @warning If the thread priority is higher or equal than the priority of the calling thread, calling thread will get paused. Use m3d::Thread::getCurrentPriority() to get the priority of the current thread
         */
        void setPriority(m3d::Thread::Priority t_priority);

        /**
         * @brief Sets the priority for the next thread that get's started
         * @param t_priority The priority of the thread (Ranging from 0 to 39)
         * @note Higher priority values mean a higher priority
         * @warning If the priority exceeds this range, it will be clamped
         * @warning If the thread priority is higher or equal than the priority of the calling thread, calling thread will get paused. Use m3d::Thread::getCurrentPriority() to get the priority of the current thread
         */
        void setPriority(int t_priority);

        /**
         * @brief Sets the size of the stack that gets allocated for the next thread that get's started
         * @param t_stackSize The allocated space in bytes (rounded to multiples of 8 bytes)
         */
        void setStackSize(unsigned long long int t_stackSize);

        /**
         * @brief Starts the thread. To restart it, call Thread::join() before
         * @param t_detached Whether the thread should start detached or not
         */
        void start(bool t_detached = false);

        /**
         * @brief Detaches the thread
         */
        void detach();

        /**
         * @brief Waits for the thread to finish
         * @param t_timeout The timeout in nanoseconds. Leave it for no timeout
         */
        void join(long long unsigned int t_timeout = U64_MAX);

        /**
         * @brief Returns the priority of the calling thread
         * @return The priority of the thread
         */
        static int getCurrentPriority();

    private:
        struct ThreadData {
            m3d::Parameter m_parameter;
            std::function<void(m3d::Parameter)> m_function;
        };

        static void threadFunction(void* t_arg);

        /* data */
        int m_priority, m_stackSize;
        bool m_running, m_started;
        m3d::Thread::ThreadData m_data;
        CTRU_Thread m_thread;
    };
} /* m3d */
