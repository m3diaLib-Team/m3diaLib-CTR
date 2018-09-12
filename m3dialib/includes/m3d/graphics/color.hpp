/**
 * @file color.hpp
 * @brief Defines the color class as well as some basic colors
 */
#ifndef COLOR_H
#define COLOR_H

#pragma once
#include <cstdint>
#include <3ds.h>

/**
 * @brief Creates a new RGBA8 color
 * @param r the red component of the color to create
 * @param g the green component of the color to create
 * @param b the blue component of the color to create
 * @param a the alpha component of the color to create
 */
#define RGBA8(r, g, b, a) ((((a)&0xFF)<<24) | (((b)&0xFF)<<16) | (((g)&0xFF)<<8) | (((r)&0xFF)<<0))

/**
 * @brief Gets the red value of a RGBA8 color
 * @param  c The RGBA8 color
 * @return   The red value
 */
#define RGBA8_GET_R(c) (((c) >>  0) & 0xFF)

/**
 * @brief Gets the green value of a RGBA8 color
 * @param  c The RGBA8 color
 * @return   The green value
 */
#define RGBA8_GET_G(c) (((c) >>  8) & 0xFF)

/**
 * @brief Gets the blue value of a RGBA8 color
 * @param  c The RGBA8 color
 * @return   The blue value
 */
#define RGBA8_GET_B(c) (((c) >> 16) & 0xFF)

/**
 * @brief Gets the alpha value of a RGBA8 color
 * @param  c The RGBA8 color
 * @return   The alpha value
 */
#define RGBA8_GET_A(c) (((c) >> 24) & 0xFF)

namespace m3d {
    /**
     * @brief Namespace used for pre-defined colors
     */
    namespace colors {
        /**
         * @brief Pre-defined colors
         */
        enum Color {
            RED = RGBA8(255, 0, 0, 255),        ///< FF0000
            GREEN = RGBA8(0, 255, 0, 255),      ///< 00FF00
            BLUE = RGBA8(0, 0, 255, 255),       ///< 0000FF
            YELLOW = RGBA8(255, 255, 0, 255),   ///< FFFF00
            MAGENTA = RGBA8(255, 0, 255, 255),    ///< FF00FF
            CYAN = RGBA8(0, 255, 255, 255),     ///< 00FFFF
            WHITE = RGBA8(255, 255, 255, 255),  ///< FFFFFF
            BLACK = RGBA8(0, 0, 0, 255)         ///< 000000
        };
    } /* colors */

    /**
     * @brief The color class
     */
    class Color {
    public:
        /**
         * @brief Creates a color using an opaque black as the default color
         */
        Color();

        /**
         * @brief Creates a color from an m3d::colors::Color enum
         * @param t_color The color to use
         */
        Color(m3d::colors::Color t_color);

        /**
         * @brief Creates a color using a red, green and blue value
         * @param t_r The red value
         * @param t_g The green value
         * @param t_b The blue value
         */
        Color(uint8_t t_r, uint8_t t_g, uint8_t t_b);

        /**
         * @brief Creates a color using a red, green, blue and alpha value
         * @param t_r The red value
         * @param t_g The green value
         * @param t_b The blue value
         * @param t_a The alpha value
         */
        Color(uint8_t t_r, uint8_t t_g, uint8_t t_b, uint8_t t_a);

        /**
         * @brief Sets the red, green and blue value of the color
         * @param t_r The red value
         * @param t_g The green value
         * @param t_b The blue value
         */
        void setColor(uint8_t t_r, uint8_t t_g, uint8_t t_b);

        /**
         * @brief Sets the red, green, blue and alpha value of the color
         * @param t_r The red value
         * @param t_g The green value
         * @param t_b The blue value
         * @param t_a The alpha value
         */
        void setColor(uint8_t t_r, uint8_t t_g, uint8_t t_b, uint8_t t_a);

        /**
         * @brief Sets the red, green, blue and alpha value of the color
         * @param t_r The red value
         * @param t_g The green value
         * @param t_b The blue value
         * @param t_a The alpha value (0.0-1.0)
         */
        void setColor(uint8_t t_r, uint8_t t_g, uint8_t t_b, float t_a);

        /**
         * @brief Sets the red value of the color
         * @param t_r The red value
         */
        void setRed(uint8_t t_r);

        /**
         * @brief Returns the red value of the color
         * @return The red value
         */
        uint8_t getRed();

        /**
         * @brief Sets the green value of the color
         * @param t_g green red value
         */
        void setGreen(uint8_t t_g);

        /**
         * @brief Returns the green value of the color
         * @return The green value
         */
        uint8_t getGreen();

        /**
         * @brief Sets the blue value of the color
         * @param t_b The blue value
         */
        void setBlue(uint8_t t_b);

        /**
         * @brief Returns the blue value of the color
         * @return The blue value
         */
        uint8_t getBlue();

        /**
         * @brief Sets the alpha value of the color
         * @param t_a alpha red value
         */
        void setAlpha(uint8_t t_a);

        /**
         * @brief Returns the alpha value of the color
         * @return The alpha value
         */
        uint8_t getAlpha();

        /**
         * @brief Returns the color as an RGBA8 integer
         * @return The color in RGBA8 format
         */
        u32 getRgba8();

    private:
        /* data */
        uint8_t m_red, m_green, m_blue, m_alpha;

    };
} /* m3d */


#endif /* end of include guard: COLOR_H */
