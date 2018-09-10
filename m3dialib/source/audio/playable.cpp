#include "m3d/audio/playable.hpp"

namespace m3d {
    void m3d::Playable::onPlay(std::function<void()> t_callback) {
        m_playCallbacks.push_back(t_callback);
    }

    void m3d::Playable::onFinish(std::function<void()> t_callback) {
        m_finishCallbacks.push_back(t_callback);
    }

    // https://github.com/deltabeard/ctrmus
    m3d::Playable::FileType Playable::getFileType(const std::string& t_file) {
        FILE* file = fopen(t_file.c_str(), "rb");
        uint32_t fileSig;
        m3d::Playable::FileType filetype = m3d::Playable::FileType::Error;

        /* Failure opening file */
        if(file == NULL) return filetype;

        if(fread(&fileSig, 4, 1, file) == 0) return filetype;

        switch(fileSig) {
            // "RIFF"
            case 0x46464952:
                if(fseek(file, 4, SEEK_CUR) != 0) break;

                // "WAVE" (AVI uses "RIFF" as well)
                if(fread(&fileSig, 4, 1, file) == 0) break;

                if(fileSig != 0x45564157) break;

                char header[45];
                long int position;
                position = ftell(file);
                fseek(file, 0, SEEK_SET);
                if(fread(header, 1, 44, file) == 0) break;

                // only support 16 bit PCM WAV
                if (((header[35] << 8) + (header[34])) != 16) break;
                fseek(file, position, SEEK_SET);

                filetype = m3d::Playable::FileType::Wav;
                break;

            default:
                // mp3
                if((fileSig << 16) == 0xFBFF0000 ||
                   (fileSig << 16) == 0xFAFF0000 ||
                   (fileSig << 8) == 0x33444900) {
                    filetype = m3d::Playable::FileType::Mp3;
                }
        }

        fclose(file);
        return filetype;
    }
} /* m3d */
