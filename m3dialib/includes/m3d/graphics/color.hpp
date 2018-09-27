/**
 * @file color.hpp
 * @brief Defines the color class as well as some basic colors
 */
#ifndef COLOR_H
#define COLOR_H

#pragma once
#include <cstdint>
#include <3ds.h>

namespace m3d {
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

        /**
         * @brief Returns the color as an RGB8 integer
         * @return The color in RGB8 format
         */
        u32 getRgb8();

        /**
         * @brief Converts four color components to RGBA8 format
         * @param  t_red   The red component
         * @param  t_green The green component
         * @param  t_blue  The blue component
         * @param  t_alpha The alpha component
         * @return         The color in RGBA8 format
         */
        static inline u32 rgba8(int t_red, int t_green, int t_blue, int t_alpha = 255) {
            return ((((t_alpha)&0xFF)<<24) | (((t_blue)&0xFF)<<16) | (((t_green)&0xFF)<<8) | (((t_red)&0xFF)<<0));
        }

    private:
        /* data */
        uint8_t m_red, m_green, m_blue, m_alpha;

    };
} /* m3d */


#endif /* end of include guard: COLOR_H */
