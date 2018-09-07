/**
 * @file time.hpp
 * @brief Defines the Time class
 */
#pragma once
#include <3ds.h>
#include <atomic>

namespace m3d {
    /**
     * @brief The time class, used for representing time
     */
    class Time {
    public:
        /**
         * @brief Represents different time components
         */
        enum class Component {
            Hours, ///< Hours
            Minutes, ///< Minutes
            Seconds, ///< Seconds
            Milliseconds, ///< Milliseconds
            Microseconds, ///< Microseconds
            Nanoseconds ///< Nanoseconds
        };

        /**
         * @brief Initializes the time
         */
        Time();

        /**
         * @brief Initializes the time with a given amount of nanoseconds
         * @param t_nanoseconds The time in nanoseconds
         */
        Time(unsigned long long int t_nanoseconds);

        /**
         * @brief Initializes the time given another m3d::Time-object
         * @param t_time The time-object
         *
         * This method is equivalent of a copy-constructor
         */
        Time(m3d::Time& t_time);

        /**
         * @brief Sets the time with a given amount of nanoseconds
         * @param t_nanoseconds The time in nanoseconds
         */
        void setTime(unsigned long long int t_nanoseconds);

        /**
         * @brief Sets the time given another m3d::Time-object
         * @param t_time The time-object
         */
        void setTime(m3d::Time& t_time);

        /**
         * @brief Adds nanoseconds to time
         * @param t_nanoseconds The nanoseconds
         */
        void addTime(unsigned long long int t_nanoseconds);

        /**
         * @brief Adds to the time
         * @param t_time The time to add
         */
        void addTime(m3d::Time& rhs);

        /**
         * @brief Substracts nanoseconds from the time
         * @param t_nanoseconds The nanoseconds
         */
        void substractTime(unsigned long long int t_nanoseconds);

        /**
         * @brief Substracts from the time
         * @param t_time The time to substract
         */
        void substractTime(m3d::Time& rhs);

        /**
         * @brief Returns the time converted to hours
         * @return The time converted to hours
         */
        long double getAsHours();

        /**
         * @brief Returns the time converted to minutes
         * @return The time converted to minutes
         */
        long double getAsMinutes();

        /**
         * @brief Returns the time converted to seconds
         * @return The time converted to seconds
         */
        long double getAsSeconds();

        /**
         * @brief Returns the time converted to milliseconds
         * @return The time converted to milliseconds
         */
        long double getAsMilliseconds();

        /**
         * @brief Returns the time converted to microseconds
         * @return The time converted to microseconds
         */
        long double getAsMicroseconds();

        /**
         * @brief Returns the time converted to nanoseconds
         * @return The time converted to nanoseconds
         */
        long double getAsNanoseconds();

        /**
         * @brief Converts a given time component to another one
         * @param  t_from The time-component to convert from
         * @param  t_to   The time-component to convert to
         * @param  t_time The time to convert
         * @return        The converted time
         *
         * Example to convert 5 hours to nanoseconds:\n
         * `unsigned long long int ns = m3d::Time::convert(m3d::Time::Component::Hours, m3d::Time::Component::Nanoseconds, 5);`
         */
        static unsigned long long int convert(m3d::Time::Component t_from, m3d::Time::Component t_to, unsigned long long int t_time);

        /**
         * @brief Overloads the assignment operator to set the nanoseconds
         */
        m3d::Time& operator=(unsigned long long int rhs);

        /**
         * @brief Overloads the assignment operator to set it with another time object
         */
        m3d::Time& operator=(m3d::Time& rhs);

        /**
         * @brief Overloads the equal-to operator
         */
        bool operator==(m3d::Time &rhs);

        /**
         * @brief Overloads the less-than operator
         */
        bool operator<(m3d::Time &rhs);

        /**
         * @brief Overloads the less-or-equal operator
         */
        bool operator<=(m3d::Time &rhs);

        /**
         * @brief Overloads the greater-than operator
         */
        bool operator>(m3d::Time &rhs);

        /**
         * @brief Overloads the greater-or-equal operator
         */
        bool operator>=(m3d::Time &rhs);

        /**
         * @brief Overloads the addition operator to add nanoseconds
         */
        m3d::Time operator+(unsigned long long int rhs);

        /**
         * @brief Overloads the addition operator to add another time object
         */
        m3d::Time operator+(m3d::Time &rhs);

        /**
         * @brief Overloads the substraction operator to substract nanoseconds
         */
        m3d::Time operator-(unsigned long long int rhs);

        /**
         * @brief Overloads the substraction operator to substract another time object
         */
        m3d::Time operator-(m3d::Time &rhs);

    private:
        /* data */
        std::atomic<unsigned long long int> m_nanoseconds;
    };
} /* m3d */
