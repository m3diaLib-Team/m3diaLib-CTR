/**
 * @file texture.hpp
 * @brief Defines the Texture class
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include <citro2d.h>
#include <string>
#include "vertex.hpp"

namespace m3d {
    /**
     * @brief The Texture class
     * @todo Implement loading texture from memory
     */
    class Texture {
    public:
        /**
         * @brief Initializes the texture
         */
        Texture();

        /**
         * @brief Copy constructor
         * @param t_texture The texture to copy
         */
        Texture(m3d::Texture& t_texture);

        /**
         * @brief Destroys the texture
         */
        ~Texture();

        /**
         * @brief Loads a texture from a file (png)
         * @param t_filename The name of the file you want to load
         * @return           Whether the load was successful or not
         */
        bool loadFromFile(const std::string& t_filename);

        /**
         * @brief Loads a texture from a buffer (png)
         * @param t_buffer The buffer to load the texture from
         * @return         Whether the load was successful or not
         */
        bool loadFromBuffer(const void* t_buffer);

        /**
         * @brief Returns the width of the texture
         * @return The width in pixels
         */
        int getWidth();

        /**
         * @brief Returns the height of the texture
         * @return The height in pixels
         */
        int getHeight();

        /**
         * @brief Returns the calculated width of the texture (the width rounded to the next power of 2)
         * @return The calculated width
         */
        int getCalculatedWidth();

        /**
         * @brief Returns the calculated height of the texture (the height rounded to the next power of 2)
         * @return The calculated height
         */
        int getCalculatedHeight();

        /**
         * @brief Returns the path of the loaded file
         * @return The path of the file
         */
        std::string getPath();

        /**
         * @brief Returns a reference to the C3D texture
         * @return The C3D texture
         */
        C3D_Tex* getTexture();

        /**
         * @brief Returns the Tex3DS-Subtexture of the texture
         * @return The subtexture
         */
        Tex3DS_SubTexture& getSubtexture();

        /**
         * @brief Returns a C2D_Image of the texture
         * @return The C2D_Image
         */
        C2D_Image& getImage();

        /**
         * @brief Overloads the assignment operator
         */
        m3d::Texture& operator=(m3d::Texture& rhs);

    private:
        enum class FileType {
            Png,
            Jpg
        };

        bool loadPng(const void* t_fp, bool t_buffer = false);
        inline void unloadImage(C2D_Image t_image);
        static inline u32 getNextPow2(u32 v);

        /* data */
        int m_width, m_height;
        std::string m_path;
        C3D_Tex* m_texture;
        C2D_Image m_image;
        Tex3DS_SubTexture m_subtexture;
    };
} /* m3d */

#endif /* end of include guard: TEXTURE_H */
