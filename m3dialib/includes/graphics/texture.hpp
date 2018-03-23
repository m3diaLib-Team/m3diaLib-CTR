/**
 * @file texture.hpp
 * @brief Defines the Texture class
 */
#pragma once
#include <3ds.h>
#include <citro3d.h>
#include <string>
#include <png.h>

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
         * @todo Add VRAM support
         * @todo Implement hardware tiling
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
        static void readPngFileFn(png_structp t_png_ptr, png_bytep t_data, png_size_t t_length);
        static unsigned int next_pow2(unsigned int t_v);
        static inline u32 morton_interleave(u32 t_x, u32 t_y);
        static inline u32 get_morton_offset(u32 t_x, u32 t_y, u32 t_bytes_per_pixel);
        void tileTexture32(C3D_Tex& t_tex);

        /* data */
        int m_width, m_height;
        bool m_tiled;
        std::string m_path;
        C3D_Tex m_texture;
    };
} /* m3d */
