/**
 * @file time.hpp
 * @brief Defines the Time class
 */
#ifndef TIME_H
#define TIME_H

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
        };

        /**
         * @brief Initializes the time
         */
        Time();

        /**
         * @brief Initializes the time with a given amount of milliseconds
         * @param t_milliseconds The time in milliseconds
         */
        Time(unsigned long long int t_milliseconds);

        /**
         * @brief Initializes the time given another m3d::Time-object
         * @param t_time The time-object
         *
         * This method is equivalent of a copy-constructor
         */
        Time(m3d::Time& t_time);

        /**
         * @brief Sets the time with a given amount of milliseconds
         * @param t_milliseconds The time in milliseconds
         */
        void setTime(unsigned long long int t_milliseconds);

        /**
         * @brief Sets the time given another m3d::Time-object
         * @param t_time The time-object
         */
        void setTime(m3d::Time& t_time);

        /**
         * @brief Adds milliseconds to time
         * @param t_milliseconds The milliseconds
         */
        void addTime(unsigned long long int t_milliseconds);

        /**
         * @brief Adds to the time
         * @param t_time The time to add
         */
        void addTime(m3d::Time& rhs);

        /**
         * @brief Substracts milliseconds from the time
         * @param t_milliseconds The milliseconds
         */
        void substractTime(unsigned long long int t_milliseconds);

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
         * @brief Returns the current unix timestamp in milliseconds
         * @return The timestamp
         */
        static unsigned long int getTimestamp();

        /**
         * @brief Converts a given time component to another one
         * @param  t_from The time-component to convert from
         * @param  t_to   The time-component to convert to
         * @param  t_time The time to convert
         * @return        The converted time
         *
         * Example to convert 5 hours to milliseconds:\n
         * `unsigned long long int ns = m3d::Time::convert(m3d::Time::Component::Hours, m3d::Time::Component::Milliseconds, 5);`
         */
        static long double convert(m3d::Time::Component t_from, m3d::Time::Component t_to, unsigned long long int t_time);

        /**
         * @brief Overloads the assignment operator to set the milliseconds
         */
        m3d::Time& operator=(unsigned long long int rhs);

        /**
         * @brief Overloads the assignment operator to set it with another time object
         */
        m3d::Time& operator=(m3d::Time& rhs);

        /**
         * @brief Overloads the equal-to operator with milliseconds
         */
        bool operator==(const unsigned long long int t_milliseconds);

        /**
         * @brief Overloads the equal-to operator
         */
        bool operator==(m3d::Time &rhs);

        /**
         * @brief Overloads the less-than operator with milliseconds
         */
        bool operator<(const unsigned long long int t_milliseconds);

        /**
         * @brief Overloads the less-than operator
         */
        bool operator<(m3d::Time &rhs);

        /**
         * @brief Overloads the less-or-equal operator with milliseconds
         */
        bool operator<=(const unsigned long long int t_milliseconds);

        /**
         * @brief Overloads the less-or-equal operator
         */
        bool operator<=(m3d::Time &rhs);

        /**
         * @brief Overloads the greater-than operator with milliseconds
         */
        bool operator>(const unsigned long long int t_milliseconds);

        /**
         * @brief Overloads the greater-than operator
         */
        bool operator>(m3d::Time &rhs);

        /**
         * @brief Overloads the greater-or-equal operator with milliseconds
         */
        bool operator>=(const unsigned long long int t_milliseconds);

        /**
         * @brief Overloads the greater-or-equal operator
         */
        bool operator>=(m3d::Time &rhs);

        /**
         * @brief Overloads the addition-assignment operator to add milliseconds
         */
        m3d::Time operator+=(unsigned long long int rhs);

        /**
         * @brief Overloads the addition-assignment operator to add another time object
         */
        m3d::Time operator+=(m3d::Time &rhs);

        /**
         * @brief Overloads the addition operator to add milliseconds
         */
        m3d::Time operator+(unsigned long long int rhs);

        /**
         * @brief Overloads the addition operator to add another time object
         */
        m3d::Time operator+(m3d::Time &rhs);

        /**
         * @brief Overloads the substraction-assignment operator to substract milliseconds
         */
        m3d::Time operator-=(unsigned long long int rhs);

        /**
         * @brief Overloads the substraction-assignment operator to substract another time object
         */
        m3d::Time operator-=(m3d::Time &rhs);

        /**
         * @brief Overloads the substraction operator to substract milliseconds
         */
        m3d::Time operator-(unsigned long long int rhs);

        /**
         * @brief Overloads the substraction operator to substract another time object
         */
        m3d::Time operator-(m3d::Time &rhs);

    private:
        /* data */
        std::atomic<unsigned long long int> m_milliseconds;
    };
} /* m3d */


#endif /* end of include guard: TIME_H */

