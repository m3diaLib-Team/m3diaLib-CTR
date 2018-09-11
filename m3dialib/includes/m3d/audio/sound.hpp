/**
 * @file sound.hpp
 * @brief Defines the Sound class
 */
#pragma once
#include <3ds.h>
#include <atomic>
#include <functional>
#include "m3d/audio/playable.hpp"
#include "m3d/core/thread.hpp"
#include "m3d/core/lock.hpp"

namespace m3d {
    /**
     * @brief Allows for quickly playing a sound or sound-effect
     */
    class Sound: public m3d::Playable {
    public:

        /**
         * @brief Initializes the sound with the given file
         * @param t_filename The path to the file
         *
         * The Sound-class currently supports the following file formats (more to come):
         *  - MP3
         *  - WAV (only 16-bit PCM)
         */
        Sound(const std::string& t_filename);

        /**
         * @brief Stops and destructs the sound
         */
        virtual ~Sound();

        /**
         * @brief Sets the file to stream the sound from
         * @param t_filename The path to the file
         */
        void setFile(const std::string& t_filename);

        /**
         * @brief Returns the file the sound get streamed from
         * @return The path to the file
         */
        const std::string& getFile();

        /**
         * @brief Starts the playback of the sound
         * @param t_waitForChannel Whether to wait for a free NDSP channel
         *
         * Due to limitations of the 3DS's hardware, only 24 NDSP channels are availiable. That means, you can play a maximum of 24 simultaneous tracks/sounds.
         *
         * When `t_waitForChannel` is set to `true`, the playback will wait until a new channel is freed if there isn't a free channel. Otherwise, the playback will immediately stop.
         */
        void play(bool t_waitForChannel = false);

        /**
         * @brief Starts the playback of the sound
         * @param t_file           The file to stream the sound from
         * @param t_waitForChannel Whether to wait for a free NDSP channel
         *
         * Due to limitations of the 3DS's hardware, only 24 NDSP channels are availiable. That means, you can play a maximum of 24 simultaneous tracks/sounds.
         *
         * When `t_waitForChannel` is set to `true`, the playback will wait until a new channel is freed if there isn't a free channel. Otherwise, the playback will immediately stop.
         */
        void play(const std::string& t_file, bool t_waitForChannel = false);

        /**
         * @brief Sets the volume of the music
         * @param t_volume The volume
         */
        void setVolume(float t_volume, m3d::Playable::Side t_side = m3d::Playable::Side::Both);

        /**
         * @brief Returns the current volume of the music
         * @param t_side The side to get the volume from
         * @return       The volume
         */
        float getVolume(m3d::Playable::Side t_side);

    private:
        void playLoop(m3d::Parameter);

        /* data */
        int m_position;
        std::atomic<float> m_volumeLeft, m_volumeRight;
        bool m_started;
        std::atomic<bool> m_playing, m_waitForChannel, m_ending;
        std::string m_file;
        m3d::Playable::FileType m_filetype;

        // reader
        m3d::Playable::Decoder m_decoder;
        m3d::Playable::Reader* m_reader;

        // locking
        m3d::Mutex m_mutex;
        m3d::Thread m_thread;
    };
} /* m3d */
