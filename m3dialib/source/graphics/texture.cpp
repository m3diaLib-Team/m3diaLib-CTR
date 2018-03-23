#include "graphics/texture.hpp"
#include <jpeglib.h>

namespace m3d {
    Texture::Texture() :
    m_width(0),
    m_height(0),
    m_tiled(false),
    m_path("") { /* do nothing */ }

    Texture::~Texture() {
        C3D_TexDelete(&m_texture);
    }

    bool Texture::loadFromFile(const std::string& t_filename) {
        if (t_filename.substr(t_filename.length() - 4) == ".png")
            return loadPngFile(t_filename);
        else if (t_filename.substr(t_filename.length() - 4) == ".jpg"
            || t_filename.substr(t_filename.length() - 5) == ".jpeg")
            return loadJpgFile(t_filename);

        return false;
    }

    int Texture::getWidth() {
        return m_width;
    }

    int Texture::getHeight() {
        return m_height;
    }

    std::string Texture::getPath() {
        return m_path;
    }

    C3D_Tex& Texture::getTexture() {
        return m_texture;
    }

    m3d::Texture& Texture::operator=(m3d::Texture& rhs) {
        if(this == &rhs) return *this;

        m_width = rhs.getWidth();
        m_height = rhs.getHeight();
        m_path = rhs.getPath();
        C3D_TexDelete(&m_texture);
        m_texture = rhs.getTexture();

        return *this;
    }

    // private methods
    void Texture::readPngFileFn(png_structp t_png_ptr, png_bytep t_data, png_size_t t_length) {
        FILE* fp = (FILE*) png_get_io_ptr(t_png_ptr);
        fread(t_data, 1, t_length, fp);
    }

    //Grabbed from: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
    unsigned int Texture::next_pow2(unsigned int t_v) {
        t_v--;
        t_v |= t_v >> 1;
        t_v |= t_v >> 2;
        t_v |= t_v >> 4;
        t_v |= t_v >> 8;
        t_v |= t_v >> 16;
        t_v++;

        return t_v >= 64 ? t_v : 64; // 64 = minimum texture size
    }

    // Grabbed from Citra Emulator (citra/src/video_core/utils.h)
    u32 Texture::morton_interleave(u32 t_x, u32 t_y) {
        u32 i = (t_x & 7) | ((t_y & 7) << 8); // ---- -210
        i = (i ^ (i << 2)) & 0x1313;      // ---2 --10
        i = (i ^ (i << 1)) & 0x1515;      // ---2 -1-0
        i = (i | (i >> 7)) & 0x3F;
        return i;
    }

    //Grabbed from Citra Emulator (citra/src/video_core/utils.h)
    u32 Texture::get_morton_offset(u32 t_x, u32 t_y, u32 t_bytes_per_pixel) {
        u32 i = morton_interleave(t_x, t_y);
        unsigned int offset = (t_x & ~7) * 8;
        return (i + offset) * t_bytes_per_pixel;
    }

    void Texture::tileTexture32(C3D_Tex& t_tex) {
        if (m_tiled) return;

        // TODO: add support for non-RGBA8 textures
        u8* tmp = (u8*) linearAlloc(t_tex.width * t_tex.height * 4);

        for (int j = 0; j < t_tex.height; j++) {
            for (int i = 0; i < t_tex.width; i++) {

                u32 coarse_y = j & ~7;
                u32 dst_offset = get_morton_offset(i, j, 4) + coarse_y * t_tex.width * 4;

                u32 v = ((u32*) t_tex.data)[i + (t_tex.height - 1 - j) * t_tex.width];
                *(u32*) (tmp + dst_offset) = __builtin_bswap32(v); /* RGBA8 -> ABGR8 */
            }
        }

        memcpy(t_tex.data, tmp, t_tex.width * t_tex.height * 4);
        linearFree(tmp);

        m_tiled = true;
    }

    bool Texture::loadPngFile(const std::string& t_filename) {
        const int PNG_SIGSIZE = 8;

        // this was shamelessly stolen from xerpi's sfillib
        png_byte pngsig[PNG_SIGSIZE];
        FILE* fp;

        if ((fp = fopen(t_filename.c_str(), "rb")) == NULL) {
            return false;
        }

        if (fread(pngsig, 1, PNG_SIGSIZE, fp) != PNG_SIGSIZE) {
            fclose(fp);
            return false;
        }

        if (png_sig_cmp(pngsig, 0, PNG_SIGSIZE) != 0) {
            fclose(fp);
            return false;
        }


        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (png_ptr == NULL) {
            return false;
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == NULL) {
            png_destroy_read_struct(&png_ptr, (png_infopp) 0, (png_infopp) 0);
        }

        png_bytep* row_ptrs = NULL;

        if (setjmp(png_jmpbuf(png_ptr))) {
            png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) 0);

            if (row_ptrs != NULL)
                delete row_ptrs;

            return false;
        }

        png_set_read_fn(png_ptr, (png_voidp) fp, readPngFileFn);
        png_set_sig_bytes(png_ptr, PNG_SIGSIZE);
        png_read_info(png_ptr, info_ptr);

        unsigned int width, height;
        int bit_depth, color_type;

        png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
                     &color_type, NULL, NULL, NULL);

        if ((color_type == PNG_COLOR_TYPE_PALETTE && bit_depth <= 8)
            || (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
            || png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)
            || (bit_depth == 16)) {
                png_set_expand(png_ptr);
        }

        if (bit_depth == 16)
            png_set_scale_16(png_ptr);

        if (bit_depth == 8 && color_type == PNG_COLOR_TYPE_RGB)
            png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

        if (color_type == PNG_COLOR_TYPE_GRAY) {
            png_set_gray_to_rgb(png_ptr);
            png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
        } else if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
            png_set_gray_to_rgb(png_ptr);
        }

        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            png_set_palette_to_rgb(png_ptr);
            png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
        }

        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
            png_set_tRNS_to_alpha(png_ptr);

        if (bit_depth < 8)
            png_set_packing(png_ptr);

        png_read_update_info(png_ptr, info_ptr);

        row_ptrs = (png_bytep*) malloc(sizeof(png_bytep) * height);
        if (!row_ptrs)
            png_destroy_info_struct(png_ptr, &info_ptr);

        m_width = width;
        m_height = height;

        bool success;
        C3D_Tex tex;
        success = C3D_TexInit(&tex, next_pow2(width), next_pow2(height), GPU_RGBA8);

        if (!success)
            return false;

        int stride = tex.width * 4;

        for (unsigned int i = 0; i < height; i++) {
            row_ptrs[i] = (png_bytep) (tex.data + i * stride);
        }

        png_read_image(png_ptr, row_ptrs);

        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) 0);
        free(row_ptrs);

        tileTexture32(tex);

        m_texture = tex;
        fclose(fp);
        return true;
    }

    bool Texture::loadJpgFile(const std::string& t_filename) {
        FILE* fp;
        if ((fp = fopen(t_filename.c_str(), "rb")) < 0) {
            return NULL;
        }

        struct jpeg_decompress_struct jinfo;
        struct jpeg_error_mgr jerr;

        jinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&jinfo);
        jpeg_stdio_src(&jinfo, fp);
        jpeg_read_header(&jinfo, 1);

        int row_bytes;
        switch (jinfo.jpeg_color_space) {
            case JCS_RGB:
                row_bytes = jinfo.image_width * 3;
                break;
            case JCS_YCbCr:
                jinfo.out_color_space = JCS_RGB;
                row_bytes = jinfo.image_width * 3;
                break;
            default:
                jpeg_abort_decompress(&jinfo);
                return false;
        }

        // TODO: Support JCS_GRAYSCALE, JCS_CMYK, and JCS_YCCK?
        jpeg_start_decompress(&jinfo);

        int width = jinfo.image_width, height = jinfo.image_height;

        m_width = width;
        m_height = height;

        bool success;
        C3D_Tex tex;
        success = C3D_TexInit(&tex, next_pow2(width), next_pow2(height), GPU_RGBA8);

        if (!success)
            return false;

        JSAMPARRAY buffer = (JSAMPARRAY) malloc(sizeof(JSAMPROW));
        buffer[0] = (JSAMPROW) malloc(sizeof(JSAMPLE) * row_bytes);

        unsigned int color;
        const unsigned char* jpeg_ptr;
        unsigned int* row_ptr = (unsigned int*) tex.data;

        while (jinfo.output_scanline < jinfo.output_height) {
            jpeg_read_scanlines(&jinfo, buffer, 1);
            unsigned int* tex_ptr = row_ptr;
            for (int i = 0, jpeg_ptr = (int) buffer[0]; i < jinfo.output_width; i++, jpeg_ptr += 3) {
                color  = (int) jpeg_ptr[(JSAMPROW) 0];
                color |= (int) jpeg_ptr[(JSAMPROW) 1] << 8;
                color |= (int) jpeg_ptr[(JSAMPROW) 2] << 16;
                *(tex_ptr++) = color | 0xFF000000;
            }

            row_ptr += tex.width;
        }

        jpeg_finish_decompress(&jinfo);

        free(buffer[0]);
        free(buffer);

        tileTexture32(tex);

        jpeg_destroy_decompress(&jinfo);
        m_texture = tex;
        fclose(fp);
        return true;
    }
} /* m3d */
