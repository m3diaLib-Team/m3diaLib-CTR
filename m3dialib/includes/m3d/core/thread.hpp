/**
 * @file thread.hpp
 * @brief Defines the Thread class
 */
#pragma once
#include <3ds.h>
#include <functional>
#include <string>
#include "parameter.hpp"

using CTRU_Thread = Thread;

namespace m3d {
    class Thread {
    public:
        /**
         * @brief Default constructor
         * @note This should only be called when calling m3d::Thread::initialize() before calling m3d::Thread::start()
         */
        Thread();

        /**
         * @brief Constructs the thread
         * @param t_function  The thread function
         * @param t_parameter The parameter to pass to the function
         * @param t_autostart Whether the thread should start instantly
         * @param t_detached  Whether the thread starts detached or not
         * @param t_stackSize The stacksize allocated for the thread in bytes (rounded to multiples of 8 bytes)
         * @note t_function needs to be of type `void` and take one (and only one) parameter of type m3d::Parameter
         * @warning If the thread priority is lower than the priority of the calling thread, the thread will never get executed. Use m3d::Thread::getCurrentPriority() to get the priority of the current thread
         */
        Thread(std::function<void(m3d::Parameter)> t_function, m3d::Parameter t_parameter = nullptr, bool t_autostart = false, bool t_detached = false, unsigned long long int t_stackSize = 4 * 1024);

        /**
        * @brief Destructs the thread
        */
        virtual ~Thread();

        /**
         * @brief Initializes the thread
         * @param t_function  The thread function
         * @param t_parameter The parameter to pass to the function
         * @param t_autostart Whether the thread should start instantly
         * @param t_detached  Whether the thread starts detached or not
         * @param t_stackSize The stacksize allocated for the thread in bytes (rounded to multiples of 8 bytes)
         * @note t_function needs to be of type `void` and take one (and only one) parameter of type m3d::Parameter
         * @warning If the thread priority is lower than the priority of the calling thread, the thread will never get executed. Use m3d::Thread::getCurrentPriority() to get the priority of the current thread
         */
        void initialize(std::function<void(m3d::Parameter)> t_function, m3d::Parameter t_parameter = nullptr, bool t_autostart = false, bool t_detached = false, unsigned long long int t_stackSize = 4 * 1024);

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
         * @brief Sleeps for the given time
         * @param t_milliseconds The time to sleep in milliseconds
         */
        static void sleep(int t_milliseconds);

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
