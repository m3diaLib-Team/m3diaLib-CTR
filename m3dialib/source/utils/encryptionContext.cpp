#include <algorithm>
#include <random>
#include "m3d/utils/encryptionContext.hpp"

namespace m3d {
    EncryptionContext::EncryptionContext() {
        makeKey();
    }

    void EncryptionContext::resetKey() {
        makeKey();
    }

    const std::string EncryptionContext::encrypt(const std::string& t_data) {
        char* dataOut = new char[t_data.length()];
        m_rijndael.EncryptBlock(t_data.c_str(), dataOut);
        std::string ret = dataOut;
        delete dataOut;
        return ret;
    }

    const std::string EncryptionContext::decrypt(const std::string& t_data) {
        char* dataOut = new char[t_data.length()];
        m_rijndael.DecryptBlock(t_data.c_str(), dataOut);
        std::string ret = dataOut;
        delete dataOut;
        return ret;
    }

    // private methods
    void EncryptionContext::makeKey() {
        std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(str.begin(), str.end(), generator);
        str = str.substr(0, 16);

        m_rijndael.MakeKey(str.c_str(), "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16, 16);
    }
} /* m3d */
