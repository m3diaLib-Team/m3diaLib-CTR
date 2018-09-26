#include <cmath>
#include <cstring>
#include "m3d/core/ledPattern.hpp"

namespace m3d {
    LEDPattern::LEDPattern() :
        m_time(0),
        m_delay(0) {
        addKeyFrame(0, m3d::Color(0, 0, 0));
    }

    LEDPattern::LEDPattern(m3d::Color t_color) :
        m_time(0),
        m_delay(0) {
        addKeyFrame(0, t_color);
    }

    void LEDPattern::addKeyFrame(int t_sample, m3d::Color t_color, bool t_hold) {
        if (t_sample > 31 || t_sample < 0) return;
        m_keyFrames[t_sample] = std::make_pair(t_color, t_hold);
    }

    void LEDPattern::deleteKeyframe(int t_sample) {
        m_keyFrames.erase(t_sample);
    }

    void LEDPattern::clearKeyframes() {
        m_keyFrames.clear();
    }

    void LEDPattern::setTime(float t_time) {
        m_time = t_time;
    }

    float LEDPattern::getTime() {
        return m_time;
    }

    void LEDPattern::setDelay(float t_delay) {
        m_delay = t_delay;
    }

    float LEDPattern::getDelay() {
        return m_delay;
    }

    void LEDPattern::play() {
        if (m3d::priv::core::ptmsysmHandle != 0) {
            m3d::LEDPattern::Pattern pat;

            std::map<int, std::pair<m3d::Color, bool>>::iterator it;

            for (it = m_keyFrames.begin(); it != m_keyFrames.end(); it++) {
                m3d::Color col1, col2;
                int sample1, sample2;
                bool hold;

                if (std::next(it) == m_keyFrames.end()) {
                    col1 = it->second.first;
                    col2 = it->second.first;
                    sample1 = it->first;
                    sample2 = 31;
                    hold = true;
                } else {
                    col1 = it->second.first;
                    sample1 = it->first;

                    auto next = std::next(it);
                    col2 = next->second.first;
                    sample2 = next->first;
                    hold = next->second.second;
                }

                int length = sample2 - sample1;
                int stepRed = (int) std::floor((col2.getRed() - col1.getRed()) / length);
                int stepGreen = (int) std::floor((col2.getGreen() - col1.getGreen()) / length);
                int stepBlue = (int) std::floor((col2.getBlue() - col1.getBlue()) / length);
                int red = col1.getRed(), green = col1.getGreen(), blue = col2.getBlue();

                for (int i = sample1; i <= sample2; i++) {
                    if (i != sample2) {
                        if (!hold) {
                            pat.r[i] = red;
                            pat.g[i] = green;
                            pat.b[i] = blue;

                            red += stepRed;
                            green += stepGreen;
                            blue += stepBlue;
                        } else {
                            pat.r[i] = red;
                            pat.g[i] = green;
                            pat.b[i] = blue;
                        }
                    } else {
                        pat.r[i] = col2.getRed();
                        pat.g[i] = col2.getGreen();
                        pat.b[i] = col2.getBlue();
                    }
                }
            }

            pat.unknown1 = 0;
            float tempVal = m_time * 0x10;
            if (tempVal >= 0x100) tempVal = 0xFF;
            pat.delay = (u8)tempVal;

            pat.smooth = (u8) 0x00;

            tempVal = m_delay * 0x10;
            if (tempVal >= 0x100) tempVal = 0xFF;
            pat.loop_delay = (u8)tempVal;

            u32* ipc = getThreadCommandBuffer();
            ipc[0] = 0x8010640;
            memcpy(&ipc[1], &pat, 0x64);
            Result ret = svcSendSyncRequest(m3d::priv::core::ptmsysmHandle);

            if (ret >= 0) {
                m3d::priv::core::ledPatternRunning = true;
            }
        }
    }

    bool LEDPattern::isPlaying() {
        return m3d::priv::core::ledPatternRunning;
    }

    void LEDPattern::stop() {
        if (!m3d::priv::core::ledPatternRunning || m3d::priv::core::ptmsysmHandle == 0) return;

        m3d::LEDPattern::Pattern pat = {0};
        u32* ipc = getThreadCommandBuffer();
        ipc[0] = 0x8010640;
        memcpy(&ipc[1], &pat, 0x64);
        svcSendSyncRequest(m3d::priv::core::ptmsysmHandle);
        m3d::priv::core::ledPatternRunning = false;
    }
} /* m3d */
