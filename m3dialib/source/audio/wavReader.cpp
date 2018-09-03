#include "audio/playable.hpp"

namespace m3d {
    void Playable::WavReader::set(m3d::Playable::Decoder& t_decoder) {
        t_decoder.init = std::bind(&m3d::Playable::WavReader::init, this, std::placeholders::_1);
        t_decoder.getRate = std::bind(&m3d::Playable::WavReader::getRate, this);
        t_decoder.getChannels = std::bind(&m3d::Playable::WavReader::getChannels, this);
        t_decoder.m_buffSize = m_buffSize;
        t_decoder.decode = std::bind(&m3d::Playable::WavReader::decode, this, std::placeholders::_1);
        t_decoder.exit = std::bind(&m3d::Playable::WavReader::exit, this);
        t_decoder.reset = std::bind(&m3d::Playable::WavReader::reset, this);
    }

    int Playable::WavReader::init(const std::string& t_file) {
        m_file = fopen(t_file.c_str(), "rb");

        if(m_file == NULL)
            return -1;

        fread(m_header, 1, 44, m_file);
        m_channels = (m_header[23] << 8) + (m_header[22]);

        switch(m_channels) {
            // if it's anything other than mono or stereo, break
            case 1:
            case 2:
                break;

            default:
                return -1;
        }

        return 0;
    }

    uint32_t Playable::WavReader::getRate() {
        return (m_header[27] << 24) + (m_header[26] << 16) + (m_header[25] << 8) + (m_header[24]);
    }

    uint8_t Playable::WavReader::getChannels() {
        return m_channels;
    }

    uint64_t Playable::WavReader::decode(void* t_buffer) {
        return fread(t_buffer, 1, m_buffSize, m_file) / sizeof(int16_t);
    }

    void Playable::WavReader::exit() {
        fclose(m_file);
    }

    void Playable::WavReader::reset() {
        fseek(m_file, 44, SEEK_SET);
    }
} /* m3d */
