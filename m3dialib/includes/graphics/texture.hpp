/**
 * @file texture.hpp
 * @brief Defines the Texture class
 */
#pragma once
#include <3ds.h>
#include <citro3d.h>
#include <string>

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
         * @brief Loads a texture from a file (png or jpeg)
         * @param  t_filename The name of the file you want to load
         * @return            Whether the load was successful or not
         * @todo Implement bmp support
         */
        bool loadFromFile(std::string t_filename);

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
         * @brief Returns the path of the loaded file
         * @return The path of the file
         */
        std::string getPath();

        /**
         * @brief Returns a reference to the C3D texture
         * @return The C3D texture
         */
        C3D_Tex& getTexture();

        /**
         * @brief Overloads the assignment operator
         */
        m3d::Texture& operator=(m3d::Texture& rhs);

    private:
        /* data */
        int m_width, m_height;
        std::string m_path;
        C3D_Tex m_texture;
    };
} /* m3d */
