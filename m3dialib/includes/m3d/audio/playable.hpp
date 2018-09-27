/**
 * @file playable.hpp
 * @brief Defines the base class for all playable classes
 */
#ifndef PLAYABLE_H
#define PLAYABLE_H

#pragma once
#include <3ds.h>
#include <functional>
#include <mpg123.h>
#include <vector>

namespace m3d {
    /**
     * @brief The base class for all playable classes.
     *
     * To create your own playable class, create a child class of this one and implement the play()-method.
     */
    class Playable {
    public:
        /**
         * @brief Defines the two stereo sides
         */
        enum class Side {
            Left,  ///< Left stereo side
            Right, ///< Right stereo side
            Both   ///< Both stereo sides
        };

        /**
         * @brief Starts the playback of the playable
         * @param t_waitForChannel Whether to wait for a free NDSP channel
         *
         * Implement this function in your own class to draw stuff on the screen using Citro2D-functions.
         *
         * Due to limitations of the 3DS's hardware, only 24 NDSP channels are availiable. That means, you can play a maximum of 24 simultaneous tracks/sounds.
         * When `t_waitForChannel` is set to `true`, the playback will wait until a new channel is freed if there isn't a free channel. Otherwise, the playback will immediately stop.
         */
        virtual void play(bool t_waitForChannel = false) = 0;

        /**
         * @brief Sets the volume of the playable
         * @param t_volume The volume
         * @param t_side   The side to set the volume for
         */
        virtual void setVolume(float t_volume, m3d::Playable::Side t_side = m3d::Playable::Side::Both) = 0;

        /**
         * @brief Returns the current volume of the music
         * @param t_side The side to get the volume from
         * @return       The volume
         */
        virtual float getVolume(m3d::Playable::Side t_side) = 0;

        /**
         * @brief Adds a callback function to call when the playable starts playing
         * @param t_callback The callback function
         */
        virtual void onPlay(std::function<void()> t_callback);

        /**
         * @brief Adds a callback function to call when the playable has finished playing
         * @param t_callback The callback function
         */
        virtual void onFinish(std::function<void()> t_callback);

    protected:
        struct Decoder {
            std::function<int(const std::string&)> init;
            std::function<uint32_t()> getRate;
            std::function<uint8_t()> getChannels;
            size_t m_buffSize;
            std::function<void(int)> setPosition;
            std::function<int()> getPosition;
            std::function<int()> getLength;
            std::function<uint64_t(void*)> decode;
            std::function<void()> exit;
            std::function<void()> reset;
        };

        class Reader {
        public:
            virtual ~Reader() {};
            virtual void set(m3d::Playable::Decoder& t_decoder) = 0;
            virtual int init(const std::string& t_file) = 0;
            virtual uint32_t getRate() = 0;
            virtual uint8_t getChannels() = 0;
            virtual void setPosition(int t_position) = 0;
            virtual int getPosition() = 0;
            virtual int getLength() = 0;
            virtual uint64_t decode(void* t_buffer) = 0;
            virtual void exit() = 0;
            virtual void reset() = 0;
        };

        class MP3Reader: public m3d::Playable::Reader {
        public:
            virtual ~MP3Reader();
            void set(m3d::Playable::Decoder& t_decoder);
            int init(const std::string& t_file);
            uint32_t getRate();
            uint8_t getChannels();
            void setPosition(int t_position);
            int getPosition();
            int getLength();
            uint64_t decode(void* t_buffer);
            void exit();
            void reset();

        private:
            /* data */
            size_t* m_buffSize;
            mpg123_handle* m_handle;
            uint32_t m_rate;
            uint8_t m_channels;
        };

        class WAVReader: public m3d::Playable::Reader {
        public:
            void set(m3d::Playable::Decoder& t_decoder);
            int init(const std::string& t_file);
            uint32_t getRate();
            uint8_t getChannels();
            void setPosition(int t_position);
            int getPosition();
            int getLength();
            uint64_t decode(void* t_buffer);
            void exit();
            void reset();

        private:
            /* data */
            static const size_t m_buffSize = 16 * 1024;
            FILE* m_file;
            char m_header[45];
            uint8_t m_channels;
            int m_length;
        };

        enum class FileType {
            Error = 0,
            Mp3,
            Wav
        };

        m3d::Playable::FileType getFileType(const std::string& t_file);
        int occupyChannel(bool t_waitForChannel = false);

        /* data */
        std::vector<std::function<void()>> m_playCallbacks,
                                           m_finishCallbacks;
    };
} /* m3d */


#endif /* end of include guard: PLAYABLE_H */
