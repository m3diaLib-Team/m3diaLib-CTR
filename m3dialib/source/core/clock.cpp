#include "m3d/core/clock.hpp"

namespace m3d {
    Clock::Clock() :
            m_running(false) { /* do nothing */ }

    Clock::~Clock() {
        stop();

        if (!m_started) {
            m_thread.initialize([](m3d::Parameter){}, nullptr);
            m_thread.start();
        }
    }

    void Clock::setTime(unsigned long long int t_milliseconds) {
        m3d::Lock lock(m_mutex);
        m_time.setTime(t_milliseconds);
    }

    void Clock::setTime(m3d::Time t_time) {
        m3d::Lock lock(m_mutex);
        m_time.setTime(t_time.getAsMilliseconds());
    }

    void Clock::start() {
        if (!m_running) {
            m_reverse = false;
            m_running = true;
            m_thread.initialize(std::bind(&m3d::Clock::runningThread, this, std::placeholders::_1), nullptr);
            m_thread.start();
        }
    }

    void Clock::countdown() {
        if (!m_running) {
            m_reverse = true;
            m_running = true;
            m_thread.initialize(std::bind(&m3d::Clock::runningThread, this, std::placeholders::_1), nullptr);
            m_thread.start();
        }
    }

    void Clock::stop() {
        pause();
        m_time = 0;
    }

    void Clock::pause() {
        if (m_running) {
            m_running = false;
            m_thread.join();
        }
    }

    void Clock::reset() {
        m3d::Lock lock(m_mutex);
        m_time = 0;
    }

    m3d::Time& Clock::getTime() {
        return m_time;
    }

    // private methods
    void Clock::runningThread(m3d::Parameter) {
        m_lastCheck = m3d::Time::getTimestamp();
        unsigned long long int currentTime, timeDifference;

        while (m_running) {
             currentTime = m3d::Time::getTimestamp();

            {
                m3d::Lock lock(m_mutex);
                timeDifference = currentTime - m_lastCheck;
                m_lastCheck = currentTime;

                if (m_reverse) {
                    if (timeDifference > m_time.getAsMilliseconds()) {
                        m_time = 0;
                    } else {
                        m_time -= timeDifference;
                    }
                } else {
                    m_time += timeDifference;
                }
            }

            m3d::Thread::sleep();
        }
    }
} /* m3d */
