/**
 * @file parameter.hpp
 * @brief Defines the Parameter class
 */
#ifndef PARAMETER_H
#define PARAMETER_H

#pragma once
#include <tuple>

namespace m3d {
    /**
     * @brief A parameter that can take any type
     */
	class Parameter
    {
    private:
        using id = size_t;

        template<typename T>
        struct type { static void id() { } };

        template<typename T>
        static id type_id() { return reinterpret_cast<id>(&type<T>::id); }

        template<typename T>
        using decay = typename std::decay<T>::type;

        template<typename T>
        using none = typename std::enable_if<!std::is_same<Parameter, T>::value>::type;

        struct base
        {
            virtual ~base() { }
            virtual bool is(id) const = 0;
            virtual base *copy() const = 0;
        } *p = nullptr;

        template<typename T>
        struct data : base, std::tuple<T>
        {
            using std::tuple<T>::tuple;

            T       &get()      & { return std::get<0>(*this); }
            T const &get() const& { return std::get<0>(*this); }

            bool is(id i) const override { return i == type_id<T>(); }
            base *copy()  const override { return new data{get()}; }
        };

        template<typename T>
        T &stat() { return static_cast<data<T>&>(*p).get(); }

        template<typename T>
        T const &stat() const { return static_cast<data<T> const&>(*p).get(); }

        template<typename T>
        T &dyn() { return dynamic_cast<data<T>&>(*p).get(); }

        template<typename T>
        T const &dyn() const { return dynamic_cast<data<T> const&>(*p).get(); }

    public:
        /**
         * @brief Default constructor
         */
         Parameter() { }

         /**
          * @brief Destructs the Parameter
          */
        ~Parameter() { delete p; }

        /**
         * @brief Copy constructor
         * @param s The Parameter to copy
         */
        Parameter(Parameter &&s) : p{s.p} { s.p = nullptr; }

        /**
         * @brief Const copy constructor
         * @param s The Parameter to copy
         */
        Parameter(Parameter const &s) : p{s.p->copy()} { }

        /**
         * @brief Initializes the Parameter with the given value
         * @param x The value to initialize the Parameter with
         */
        template<typename T, typename U = decay<T>, typename = none<U>>
        Parameter(T &&x) : p{new data<U>{std::forward<T>(x)}} { }

        /**
         * @brief Overloads the assignment operator
         * @param s The value to set the Parameter to
         */
        Parameter &operator=(Parameter s) { swap(*this, s); return *this; }

        friend void swap(Parameter &s, Parameter &r) { std::swap(s.p, r.p); }

        /**
         * @brief Clears the Parameter
         */
        void clear() { delete p; p = nullptr; }

        /**
         * @brief Checks whether the Parameter is the given type
         * @tparam T The type to check
         * @return   Whether the Parameter has the given type or not
         */
        template<typename T>
        bool is() const { return p ? p->is(type_id<T>()) : false; }

        /**
         * @brief Returns the value of the Parameter
         * @tparam T The type of the Parameter
         * @return The value of the Parameter
         * @warning If the type of the Parameter doesn't match the type of it's stored value, it will result in undefined behaviour.
         */
        template<typename T> T &get() & { return stat<T>(); }
    };
} /* m3d */


#endif /* end of include guard: PARAMETER_H */
