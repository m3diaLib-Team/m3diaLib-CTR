#include "m3d/audio/playable.hpp"

namespace m3d {
    Playable::Mp3Reader::~Mp3Reader() {
        delete m_handle;
        delete m_buffSize;
    }

    void Playable::Mp3Reader::set(m3d::Playable::Decoder& t_decoder) {
        t_decoder.init = std::bind(&m3d::Playable::Mp3Reader::init, this, std::placeholders::_1);
        t_decoder.getRate = std::bind(&m3d::Playable::Mp3Reader::getRate, this);
        t_decoder.getChannels = std::bind(&m3d::Playable::Mp3Reader::getChannels, this);
        m_buffSize = &(t_decoder.m_buffSize);
        t_decoder.setPosition = std::bind(&m3d::Playable::Mp3Reader::setPosition, this, std::placeholders::_1);
        t_decoder.getPosition = std::bind(&m3d::Playable::Mp3Reader::getPosition, this);
        t_decoder.decode = std::bind(&m3d::Playable::Mp3Reader::decode, this, std::placeholders::_1);
        t_decoder.exit = std::bind(&m3d::Playable::Mp3Reader::exit, this);
        t_decoder.reset = std::bind(&m3d::Playable::Mp3Reader::reset, this);
    }

    int Playable::Mp3Reader::init(const std::string& t_file)
    {
        int err = 0;
        int encoding = 0;

        if((err = mpg123_init()) != MPG123_OK)
            return err;

        if((m_handle = mpg123_new(NULL, &err)) == NULL)
        {
            printf("Error: %s\n", mpg123_plain_strerror(err));
            return err;
        }

        if(mpg123_open(m_handle, t_file.c_str()) != MPG123_OK ||
                mpg123_getformat(m_handle, (long *) &m_rate, (int *) &m_channels, &encoding) != MPG123_OK)
        {
            printf("Trouble with mpg123: %s\n", mpg123_strerror(m_handle));
            return -1;
        }

        /*
         * Ensure that this output format will not change (it might, when we allow
         * it).
         */
        mpg123_format_none(m_handle);
        mpg123_format(m_handle, m_rate, m_channels, encoding);

        /*
         * Buffer could be almost any size here, mpg123_outblock() is just some
         * recommendation. The size should be a multiple of the PCM frame size.
         */
        *m_buffSize = mpg123_outblock(m_handle) * 16;

        return 0;
    }

    uint32_t Playable::Mp3Reader::getRate() {
        return m_rate;
    }

    uint8_t Playable::Mp3Reader::getChannels() {
        return m_channels;
    }

    void Playable::Mp3Reader::setPosition(int t_position) {
        mpg123_seek(m_handle, t_position, SEEK_SET);
    }

    int Playable::Mp3Reader::getPosition() {
        return mpg123_tell(m_handle);
    }

    uint64_t Playable::Mp3Reader::decode(void* t_buffer) {
        size_t done = 0;
        mpg123_read(m_handle, static_cast<unsigned char*>(t_buffer), *m_buffSize, &done);
        return done / (sizeof(int16_t));
    }

    void Playable::Mp3Reader::exit() {
        mpg123_close(m_handle);
        mpg123_delete(m_handle);
        mpg123_exit();
    }

    void Playable::Mp3Reader::reset() {
        mpg123_seek(m_handle, 0, SEEK_SET);
    }
} /* m3d */
