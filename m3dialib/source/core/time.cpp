#include <chrono>
#include "m3d/core/time.hpp"

namespace m3d {
    Time::Time() :
            m_nanoseconds(0) { /* do nothing */ }

    Time::Time(unsigned long long int t_nanoseconds) :
            m_nanoseconds(t_nanoseconds) { /* do nothing */ }

    Time::Time(m3d::Time& t_time) {
        setTime(t_time);
    }

    void Time::setTime(unsigned long long int t_nanoseconds) {
        m_nanoseconds = t_nanoseconds;
    }

    void Time::setTime(m3d::Time& t_time) {
        m_nanoseconds = t_time.getAsNanoseconds();
    }

    void Time::addTime(unsigned long long int t_nanoseconds) {
        m_nanoseconds += t_nanoseconds;
    }

    void Time::addTime(m3d::Time& rhs) {
        m_nanoseconds += rhs.getAsNanoseconds();
    }

    void Time::substractTime(unsigned long long int t_nanoseconds) {
        m_nanoseconds -= t_nanoseconds;
    }

    void Time::substractTime(m3d::Time& rhs) {
        m_nanoseconds -= rhs.getAsNanoseconds();
    }

    long double Time::getAsHours() {
        return (long double) m_nanoseconds / 60.f / 60.f / 1000000000.f;
    }

    long double Time::getAsMinutes() {
        return (long double) m_nanoseconds / 60.f / 1000000000.f;
    }

    long double Time::getAsSeconds() {
        return (long double) m_nanoseconds / 1000000000.f;
    }

    long double Time::getAsMilliseconds() {
        return (long double) m_nanoseconds / 1000000.f;
    }

    long double Time::getAsMicroseconds() {
        return (long double) m_nanoseconds / 1000.f;
    }

    long double Time::getAsNanoseconds() {
        return (long double) m_nanoseconds;
    }

    unsigned long int getTimestamp() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    unsigned long long int Time::convert(m3d::Time::Component t_from, m3d::Time::Component t_to, unsigned long long int t_time) {
        long double nanoseconds;

        switch (t_from) {
            case m3d::Time::Component::Hours:
                nanoseconds = (long double) t_time * 60.f * 60.f * 1000000000.f;
                break;
            case m3d::Time::Component::Minutes:
                nanoseconds = (long double) t_time * 60.f * 1000000000.f;
                break;
            case m3d::Time::Component::Seconds:
                nanoseconds = (long double) t_time * 1000000000.f;
                break;
            case m3d::Time::Component::Milliseconds:
                nanoseconds = (long double) t_time * 1000000.f;
                break;
            case m3d::Time::Component::Microseconds:
                nanoseconds = (long double) t_time * 1000.f;
                break;
            case m3d::Time::Component::Nanoseconds:
                nanoseconds = (long double) t_time;
                break;
        }

        switch (t_to) {
            case m3d::Time::Component::Hours:
                return nanoseconds / 1000000000.f / 60.f / 60.f;
            case m3d::Time::Component::Minutes:
                return nanoseconds / 1000000000.f / 60.f;
            case m3d::Time::Component::Seconds:
                return nanoseconds / 1000000000.f;
            case m3d::Time::Component::Milliseconds:
                return nanoseconds / 1000000.f;
            case m3d::Time::Component::Microseconds:
                return nanoseconds / 1000.f;
            case m3d::Time::Component::Nanoseconds:
                return nanoseconds;
        }
    }

    m3d::Time& Time::operator=(unsigned long long int rhs) {
        m_nanoseconds = rhs;
        return *this;
    }

    m3d::Time& Time::operator=(m3d::Time& rhs) {
        m_nanoseconds = rhs.getAsNanoseconds();
        return *this;
    }

    bool Time::operator==(m3d::Time &rhs) {
        return m_nanoseconds == rhs.getAsNanoseconds();
    }

    bool Time::operator<(m3d::Time &rhs) {
        return m_nanoseconds < rhs.getAsNanoseconds();
    }

    bool Time::operator<=(m3d::Time &rhs) {
        return m_nanoseconds <= rhs.getAsNanoseconds();
    }

    bool Time::operator>(m3d::Time &rhs) {
        return m_nanoseconds > rhs.getAsNanoseconds();
    }

    bool Time::operator>=(m3d::Time &rhs) {
        return m_nanoseconds >= rhs.getAsNanoseconds();
    }

    m3d::Time Time::operator+(unsigned long long int rhs) {
        addTime(rhs);
        return *this;
    }

    m3d::Time Time::operator+(m3d::Time &rhs) {
        addTime(rhs);
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
