#include <chrono>
#include "m3d/core/time.hpp"

namespace m3d {
    Time::Time() :
            m_milliseconds(0) { /* do nothing */ }

    Time::Time(unsigned long long int t_milliseconds) :
            m_milliseconds(t_milliseconds) { /* do nothing */ }

    Time::Time(m3d::Time& t_time) {
        setTime(t_time);
    }

    void Time::setTime(unsigned long long int t_milliseconds) {
        m_milliseconds = t_milliseconds;
    }

    void Time::setTime(m3d::Time& t_time) {
        m_milliseconds = t_time.getAsMilliseconds();
    }

    void Time::addTime(unsigned long long int t_milliseconds) {
        m_milliseconds += t_milliseconds;
    }

    void Time::addTime(m3d::Time& rhs) {
        m_milliseconds += rhs.getAsMilliseconds();
    }

    void Time::substractTime(unsigned long long int t_milliseconds) {
        m_milliseconds -= t_milliseconds;
    }

    void Time::substractTime(m3d::Time& rhs) {
        m_milliseconds -= rhs.getAsMilliseconds();
    }

    long double Time::getAsHours() {
        return (long double) m_milliseconds / 60.f / 60.f / 1000.f;
    }

    long double Time::getAsMinutes() {
        return (long double) m_milliseconds / 60.f / 1000.f;
    }

    long double Time::getAsSeconds() {
        return (long double) m_milliseconds / 1000.f;
    }

    long double Time::getAsMilliseconds() {
        return (long double) m_milliseconds;
    }

    unsigned long int Time::getTimestamp() {
        return osGetTime();
    }

    long double Time::convert(m3d::Time::Component t_from, m3d::Time::Component t_to, unsigned long long int t_time) {
        long double milliseconds = 0;

        switch (t_from) {
            case m3d::Time::Component::Hours:
                milliseconds = (long double) t_time * 60.f * 60.f * 1000.f;
                break;
            case m3d::Time::Component::Minutes:
                milliseconds = (long double) t_time * 60.f * 1000.f;
                break;
            case m3d::Time::Component::Seconds:
                milliseconds = (long double) t_time * 1000.f;
                break;
            case m3d::Time::Component::Milliseconds:
                milliseconds = (long double) t_time;
                break;
        }

        switch (t_to) {
            case m3d::Time::Component::Hours:
                return milliseconds / 1000.f / 60.f / 60.f;
            case m3d::Time::Component::Minutes:
                return milliseconds / 1000.f / 60.f;
            case m3d::Time::Component::Seconds:
                return milliseconds / 1000.f;
            case m3d::Time::Component::Milliseconds:
                return milliseconds;
        }

        return 0;
    }

    m3d::Time& Time::operator=(unsigned long long int rhs) {
        m_milliseconds = rhs;
        return *this;
    }

    m3d::Time& Time::operator=(m3d::Time& rhs) {
        m_milliseconds = rhs.getAsMilliseconds();
        return *this;
    }

    bool Time::operator==(const unsigned long long int t_milliseconds) {
        return m_milliseconds == t_milliseconds;
    }

    bool Time::operator==(m3d::Time &rhs) {
        return m_milliseconds == rhs.getAsMilliseconds();
    }

    bool Time::operator<(const unsigned long long int t_milliseconds) {
        return m_milliseconds < t_milliseconds;
    }

    bool Time::operator<(m3d::Time &rhs) {
        return m_milliseconds < rhs.getAsMilliseconds();
    }

    bool Time::operator<=(const unsigned long long int t_milliseconds) {
        return m_milliseconds <= t_milliseconds;
    }

    bool Time::operator<=(m3d::Time &rhs) {
        return m_milliseconds <= rhs.getAsMilliseconds();
    }

    bool Time::operator>(const unsigned long long int t_milliseconds) {
        return m_milliseconds > t_milliseconds;
    }

    bool Time::operator>(m3d::Time &rhs) {
        return m_milliseconds > rhs.getAsMilliseconds();
    }

    bool Time::operator>=(const unsigned long long int t_milliseconds) {
        return m_milliseconds >= t_milliseconds;
    }

    bool Time::operator>=(m3d::Time &rhs) {
        return m_milliseconds >= rhs.getAsMilliseconds();
    }

    m3d::Time Time::operator+=(unsigned long long int rhs) {
        addTime(rhs);
        return *this;
    }

    m3d::Time Time::operator+=(m3d::Time &rhs) {
        addTime(rhs);
        return *this;
    }

    m3d::Time Time::operator+(unsigned long long int rhs) {
        addTime(rhs);
        return *this;
    }

    m3d::Time Time::operator+(m3d::Time &rhs) {
        addTime(rhs);
        return *this;
    }

    m3d::Time Time::operator-=(unsigned long long int rhs) {
        substractTime(rhs);
        return *this;
    }

    m3d::Time Time::operator-=(m3d::Time &rhs) {
        substractTime(rhs);
        return *this;
    }

    m3d::Time Time::operator-(unsigned long long int rhs) {
        substractTime(rhs);
        return *this;
    }

    m3d::Time Time::operator-(m3d::Time &rhs) {
        substractTime(rhs);
        return *this;
    }
} /* m3d */
