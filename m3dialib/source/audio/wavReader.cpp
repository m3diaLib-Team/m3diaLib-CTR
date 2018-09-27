#include "m3d/audio/playable.hpp"

namespace m3d {
    void Playable::WAVReader::set(m3d::Playable::Decoder& t_decoder) {
        t_decoder.init = std::bind(&m3d::Playable::WAVReader::init, this, std::placeholders::_1);
        t_decoder.getRate = std::bind(&m3d::Playable::WAVReader::getRate, this);
        t_decoder.getChannels = std::bind(&m3d::Playable::WAVReader::getChannels, this);
        t_decoder.m_buffSize = m_buffSize;
        t_decoder.setPosition = std::bind(&m3d::Playable::WAVReader::setPosition, this, std::placeholders::_1);
        t_decoder.getPosition = std::bind(&m3d::Playable::WAVReader::getPosition, this);
        t_decoder.getLength = std::bind(&m3d::Playable::WAVReader::getLength, this);
        t_decoder.decode = std::bind(&m3d::Playable::WAVReader::decode, this, std::placeholders::_1);
        t_decoder.exit = std::bind(&m3d::Playable::WAVReader::exit, this);
        t_decoder.reset = std::bind(&m3d::Playable::WAVReader::reset, this);
    }

    int Playable::WAVReader::init(const std::string& t_file) {
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

        fseek(m_file, 0, SEEK_END);
        m_length = ftell(m_file) - 44;
        fseek(m_file, 44, SEEK_SET);

        return 0;
    }

    uint32_t Playable::WAVReader::getRate() {
        return (m_header[27] << 24) + (m_header[26] << 16) + (m_header[25] << 8) + (m_header[24]);
    }

    uint8_t Playable::WAVReader::getChannels() {
        return m_channels;
    }

    void Playable::WAVReader::setPosition(int t_position) {
        fseek(m_file, 44 + t_position, SEEK_SET);
    }

    int Playable::WAVReader::getPosition() {
        return m_length;
    }

    int Playable::WAVReader::getLength() {
        return ftell(m_file) - 44;
    }

    uint64_t Playable::WAVReader::decode(void* t_buffer) {
        return fread(t_buffer, 1, m_buffSize, m_file) / sizeof(int16_t);
    }

    void Playable::WAVReader::exit() {
        fclose(m_file);
    }

    void Playable::WAVReader::reset() {
        fseek(m_file, 44, SEEK_SET);
    }
} /* m3d */
