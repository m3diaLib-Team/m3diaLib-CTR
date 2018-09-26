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
        LEDPattern();

        LEDPattern(m3d::Color t_color);

        void addKeyFrame(int t_sample, m3d::Color t_color, bool t_hold = false);

        void deleteKeyframe(int t_sample);

        void clearKeyframes();

        void setTime(float t_time);

        float getTime();

        void setDelay(float t_delay);

        float getDelay();

        void play();

        static bool isPlaying();

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
