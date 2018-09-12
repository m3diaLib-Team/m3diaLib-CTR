/**
 * @file encryptionContext.hpp
 * @brief Defines the EncryptionContext-class
 */
#ifndef ENCRYPTIONCONTEXT_H
#define ENCRYPTIONCONTEXT_H

#pragma once
#include <string>
#include "crypto/rijndael.hpp"

namespace m3d {
    /**
     * @brief EncryptionContext-class used for encrypting and decrypting data
     */
    class EncryptionContext {
    public:
        /**
         * @brief EncryptionContext-class used for encrypting and decrypting data
         */
        EncryptionContext();

        /**
         * @brief Generates a new key for the context
         */
        void resetKey();

        /**
         * @brief Encrypts the given data
         * @param  t_data The data to encrypt
         * @return        The encrypted data
         */
        const std::string encrypt(const std::string& t_data);

        /**
         * @brief Decrypts the given data
         * @param  t_data The data to decrypt
         * @return        The decrypted data
         */
        const std::string decrypt(const std::string& t_data);

    private:
        void makeKey();

        /* data */
        m3d::priv::CRijndael m_rijndael;
    };
} /* m3d */


#endif /* end of include guard: ENCRYPTIONCONTEXT_H */
