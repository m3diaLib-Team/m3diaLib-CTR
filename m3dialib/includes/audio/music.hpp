/**
 * @file music.hpp
 * @brief Defines the Music class
 */
#pragma once
#include <3ds.h>
#include <atomic>
#include "audio/playable.hpp"
#include "core/thread.hpp"
#include "core/lock.hpp"

namespace m3d {
    /**
     * @brief Allows for loading, playing and manipulating music
     */
    class Music: public m3d::Playable {
    public:
        /**
         * @brief Represents the status of the music
         */
        enum class Status {
            Playing, ///< The music is playing
            Paused,  ///< The music is paused
            Stopped  ///< The music is stopped or wasn't started yet
        };

        /**
         * @brief Initializes the music with the given file
         * @param t_filename The path to the file
         *
         * The Music-class currently supports the following file formats (more to come):
         *  - MP3
         *  - WAV (only 16-bit PCM)
         */
        Music(const std::string& t_filename);

        /**
         * @brief Stops and destructs the music
         */
        virtual ~Music();

        /**
         * @brief Sets the file to stream the music from
         * @param t_filename The path to the file
         * @note This stops the current music
         */
        void setFile(const std::string& t_filename);

        /**
         * @brief Returns the file the music get streamed from
         * @return The path to the file
         */
        const std::string& getFile();

        /**
         * @brief Starts the playback of the music
         * @param t_waitForChannel Whether to wait for a free NDSP channel
         *
         * Due to limitations of the 3DS's hardware, only 24 NDSP channels are availiable. That means, you can play a maximum of 24 simultaneous tracks/sounds.
         *
         * When `t_waitForChannel` is set to `true`, the playback will wait until a new channel is freed if there isn't a free channel. Otherwise, the playback will immediately stop.
         */
        void play(bool t_waitForChannel = false);

        /**
         * @brief Pauses the playback
         */
        void pause();

        /**
         * @brief Stops the playback and set's the time back to 0
         */
        void stop();

        /**
         * @brief Toggles between pause and play
         */
        void togglePlay();

        /**
         * @brief Returns the current play-status of the music
         * @return The current play-status
         */
        m3d::Music::Status getPlayStatus();

        void setVolume(float t_volume);

        float getVolume();

        /**
         * @brief Sets the looping-mode of the music
         * @param t_loop Whether to loop or not
         */
        void loop(bool t_loop);

        /**
         * @brief Returns the looping-mode of the music
         * @return Whether the music loops or not
         */
        bool getLoop();

        /**
         * @brief Adds a callback function to call when the music was paused
         * @param t_callback The callback function
         */
        void onPause(std::function<void()> t_callback);

        /**
         * @brief Adds a callback function to call when the music has looped
         * @param t_callback The callback function
         */
        void onLoop(std::function<void()> t_callback);

        /**
         * @brief Adds a callback function to call when the music has stopped playing
         * @param t_callback The callback function
         *
         * The callback function needs to take one argument of type `bool` which is true if the music was stopped because the music has finished playing and false when it was stopped for another reason
         */
        void onStop(std::function<void(bool)> t_callback);

    private:
        void playFile(m3d::Parameter t_waitForChannel);

        /* data */
        int m_position;
        std::atomic<float> m_volume;
        bool m_started;
        std::atomic<bool> m_loop, m_volumeChanged;
        std::string m_file;
        m3d::Playable::FileType m_filetype;
        std::atomic<m3d::Music::Status> m_status;

        // callbacks
        std::vector<std::function<void()>> m_pauseCallbacks,
                                           m_loopCallbacks;
        std::vector<std::function<void(bool)>> m_stopCallbacks;

        // reader
        m3d::Playable::Decoder m_decoder;
        m3d::Playable::Reader* m_reader;

        // locking
        m3d::Mutex m_mutex;
        m3d::Thread m_thread;
    };
} /* m3d */
