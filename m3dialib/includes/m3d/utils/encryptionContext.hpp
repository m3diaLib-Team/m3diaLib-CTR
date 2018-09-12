#ifndef ENCRYPTIONCONTEXT_H
#define ENCRYPTIONCONTEXT_H

#pragma once
#include <string>
#include "crypto/rijndael.hpp"

namespace m3d {
    class EncryptionContext {
    public:
        EncryptionContext();

        void resetKey();

        const std::string encrypt(const std::string& t_data);

        const std::string decrypt(const std::string& t_data);

    private:
        void makeKey();

        /* data */
        m3d::priv::CRijndael m_rijndael;
    };
} /* m3d */


#endif /* end of include guard: ENCRYPTIONCONTEXT_H */
