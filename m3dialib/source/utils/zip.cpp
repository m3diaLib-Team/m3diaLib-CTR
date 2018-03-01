#include "utils/zip.hpp"
#include "zip/zip_wrapper.h"

namespace m3d {
    Zip::Zip(const std::string& t_filename) {
        setFilename(t_filename);
    }

    const std::string& Zip::getFilename() {
        return m_filename;
    }

    void Zip::setFilename(const std::string& t_filename) {
        m_filename = t_filename;

        // please, just ignore this monster of a syntax
        FILE* file;
        if ((file = fopen(t_filename.c_str(), "r")) == nullptr) {
            struct zip_t* zip = zip_open(t_filename.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
            zip_close(zip);
            delete file;
        }
    }

    void Zip::addFile(const std::string& t_filename, const std::string& t_newFilename) {
        struct zip_t* zip = zip_open(m_filename.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'a');
        zip_entry_open(zip, t_newFilename.c_str());
        zip_entry_fwrite(zip, t_filename.c_str());
        zip_entry_close(zip);
        zip_close(zip);
    }

    void Zip::addFileByContent(const std::string& t_content, const std::string& t_filename) {
        struct zip_t* zip = zip_open(m_filename.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
        zip_entry_open(zip, t_filename.c_str());
        zip_entry_write(zip, t_content.c_str(), strlen(t_content.c_str()));
        zip_entry_close(zip);
        zip_close(zip);
    }

    const std::string Zip::readFile(const std::string& t_filename) {
        struct zip_t* zip = zip_open(m_filename.c_str(), 0, 'r');

        void* buf = NULL;
        size_t bufsize;

        zip_entry_open(zip, t_filename.c_str());
        {
            zip_entry_read(zip, &buf, &bufsize);
        }
        zip_entry_close(zip);
        zip_close(zip);

        std::string ret = std::string((const char*) buf, bufsize);
        delete (const char*) buf;

        return ret;
    }

    void Zip::extractFile(const std::string& t_fileName, const std::string& t_path) {
        struct zip_t* zip = zip_open(m_filename.c_str(), 0, 'r');
        zip_entry_open(zip, t_fileName.c_str());
        zip_entry_fread(zip, t_path.c_str());
        zip_entry_close(zip);
        zip_close(zip);
    }

    void Zip::extract(const std::string& t_path) {
        zip_extract(m_filename.c_str(), t_path.c_str(), nullptr, nullptr);
    }

    std::vector<ZipEntry> Zip::getEntries() {
        std::vector<ZipEntry> entries;
        ZipEntry currentEntry;

        struct zip_t* zip = zip_open(m_filename.c_str(), 0, 'r');
        int n = zip_total_entries(zip);

        for (int i = 0; i < n; ++i) {
            zip_entry_openbyindex(zip, i);
            const char *name = zip_entry_name(zip);
            int isdir = zip_entry_isdir(zip);

            currentEntry.name = std::string(name, strlen(name));
            currentEntry.isDir = (isdir == 1);
        }

        zip_entry_close(zip);
        zip_close(zip);

        return entries;
    }
} /* m3d */
