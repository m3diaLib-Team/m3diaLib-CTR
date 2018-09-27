/**
 * @file ledPattern.hpp
 * @brief Defines the LEDPattern class
 */
/*
 * Credits for a lot of the internal code to https://github.com/mariohackandglitch/ctr-led-brary
 */
#ifndef LEDPATTERN_H
#define LEDPATTERN_H

#pragma once
#include <3ds.h>
#include <map>
#include <utility>
#include "m3d/graphics/color.hpp"
#include "m3d/private/core.hpp"

namespace m3d {
    /**
     * @brief The LEDPattern class, used for manipulating the notifications LED
     */
    class LEDPattern {
    public:
        /**
         * @brief Constructs the LED pattern
         */
        LEDPattern();

        /**
         * @brief Initializes the LED pattern with a constant color
         * @param t_color The color
         */
        LEDPattern(m3d::Color t_color);

        /**
         * @brief Adds a keyframe to the pattern
         * @param t_sample The sample-position of the keyframe
         * @param t_color  The color of the keyframe
         * @param t_hold   Whether to hold the value of the last keyframe until this one or not
         */
        void addKeyFrame(int t_sample, m3d::Color t_color, bool t_hold = false);

        /**
         * @brief Deletes the keyframe at the given sample-position
         * @param t_sample The sample-position
         */
        void deleteKeyframe(int t_sample);

        /**
         * @brief Clears all keyframes
         */
        void clearKeyframes();

        /**
         * @brief Sets the time the pattern should play until it starts again
         * @param t_time The time in seconds (ranging from 0.25 to 16.0)
         */
        void setTime(float t_time);

        /**
         * @brief Returns the time the pattern plays until it starts again
         * @return The time in seconds
         */
        float getTime();

        /**
         * @brief Sets the time the pattern should wait before it starts again
         * @param t_time The time in seconds (ranging from 0 to 16)
         * @note When a time >16 is set, the pattern won't loop but will instead keep displaying the last color until it is either stopped or a different pattern is played
         */
        void setDelay(float t_delay);

        /**
         * @brief Returns the time the pattern waits before it starts again
         * @return The time in seconds
         */
        float getDelay();

        /**
         * @brief Plays the pattern
         */
        void play();

        /**
         * @brief Returns whether a pattern is currently playing or not
         * @return `true` if there is an LED pattern playing, `false` otherwise
         */
        static bool isPlaying();

        /**
         * @brief Stops any LED pattern that's currently active
         */
        static void stop();

    private:
        struct Pattern
        {
            u8 delay;
            u8 smooth;
            u8 loop_delay;
            u8 unknown1;
            u8 r[32];
            u8 g[32];
            u8 b[32];
        };

        /* data */
        std::map<int, std::pair<m3d::Color, bool>> m_keyFrames;
        float m_time, m_delay;

    };
} /* m3d */


#endif /* end of include guard: LEDPATTERN_H */
