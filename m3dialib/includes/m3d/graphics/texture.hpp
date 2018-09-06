/**
 * @file texture.hpp
 * @brief Defines the Texture class
 */
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
         * @brief Destroys the texture
         */
        ~Texture();

        /**
         * @brief Loads a texture from a file (png)
         * @param  t_filename The name of the file you want to load
         * @return            Whether the load was successful or not
         */
        bool loadFromFile(const std::string& t_filename);

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
        bool loadPng(FILE* t_fp);
        void unloadImage(C2D_Image t_image);
        static u32 getNextPow2(u32 v);

        /* data */
        int m_width, m_height;
        std::string m_path;
        C3D_Tex* m_texture;
        C2D_Image m_image;
        Tex3DS_SubTexture m_subtexture;
    };
} /* m3d */
