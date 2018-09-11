/**
 * @file music.hpp
 * @brief Defines the Music class
 */
#pragma once
#include <3ds.h>
#include <atomic>
#include "m3d/audio/playable.hpp"
#include "m3d/core/lock.hpp"
#include "m3d/core/thread.hpp"
#include "m3d/core/time.hpp"

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
         * @brief Represents different filter types
         */
        enum class Filter {
            None,     ///< Disables filter
            LowPass,  ///< Lowpass filter. %Parameter is the cut-off frequency
            HighPass, ///< Highpass filter. %Parameter is the cut-off frequency
            BandPass, ///< Bandpass filter. %Parameter is the mid-frequency
            Notch     ///< Notch filter. %Parameter is the notch-frequency
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

        /**
         * @brief Sets the play-offset of the music in samples
         * @param t_position The play-offset
         */
        void setPosition(int t_position);

        /**
         * @brief Sets the play-offset of the music
         * @param t_position The play-offset
         */
        void setPosition(m3d::Time t_position);

        /**
         * @brief Returns the play-offset of the music in samples
         * @return The play-offset
         */
        int getPosition();

        /**
         * @brief Returns the samplerate of the music
         * @return The samplerate
         */
        int getSampleRate();

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

        /**
         * @brief Returns the currently occupied dsp-channel
         * @return The current channel
         */
        int getChannel();

        /**
         * @brief Disables the filter for the music
         */
        void disableFilter();

        /**
         * @brief Sets the filter for the music
         * @param t_filter    The filter-type
         * @param t_frequency The filter-frequency
         * @note The recommended frequency range for the filter is between 30Hz and 16kHz (16,000Hz)
         */
        void setFilter(m3d::Music::Filter t_filter, float t_frequency);

        /**
         * @brief Returns the current audio-frame
         * @return The current audio-frame
         */
        const std::vector<int16_t> getCurrentFrame();

    private:
        void playFile(m3d::Parameter t_waitForChannel);

        /* data */
        std::atomic<int> m_position, m_channel;
        std::atomic<float> m_volumeLeft, m_volumeRight, m_filterFrequency;
        bool m_started;
        std::atomic<bool> m_loop;
        std::string m_file;
        m3d::Playable::FileType m_filetype;
        std::atomic<m3d::Music::Status> m_status;
        std::atomic<m3d::Music::Filter> m_filter;
        std::vector<int16_t> m_currentFrame;

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
