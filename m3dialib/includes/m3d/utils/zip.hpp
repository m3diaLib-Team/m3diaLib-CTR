/**
 * @file zip.hpp
 * @brief Defines the zip class
 */
#ifndef ZIP_H
#define ZIP_H

#pragma once
#include <vector>
#include <string>

namespace m3d {
    /**
     * @brief Represents an entry in a zip file
     */
    struct ZipEntry {
        std::string name; ///< The file name
        bool isDir;       ///< Whether the entry is a directory (true if it is, false otherwise)
    };

    /**
     * @brief The zip class
     */
    class Zip {
    public:
        /**
         * @brief The constructor
         * @param t_filename The filename of the zip file
         */
        Zip(const std::string& t_filename);

        /**
         * @brief Returns the current filename
         * @return The filename that is currently being worked with
         */
        const std::string& getFilename();

        /**
         * @brief Sets the new filename to work with
         * @param t_filename The filename of the zip file
         */
        void setFilename(const std::string& t_filename);

        /**
         * @brief Adds a file into the zip file
         * @param t_filename    The filename of the file to compress
         * @param t_newFilename The new filename inside the zip (if empty, the original filename is used)
         */
        void addFile(const std::string& t_filename, const std::string& t_newFilename = "");

        /**
         * @brief Creates a new file in the zip and fills it with the given content
         * @param t_content  The content to write into the new file
         * @param t_filename The filename the new file should have
         */
        void addFileByContent(const std::string& t_content, const std::string& t_filename);

        /**
         * @brief Reads the content of a file inside the zip
         * @param  t_filename The filename ofthe file you want to read from
         * @return            The content of the file
         */
        const std::string readFile(const std::string& t_filename);

        /**
         * @brief Extracts a file from the zip to the given location
         * @param t_filename The filename of the file inside the zip
         * @param t_path     The path to extract to (including the new filename)
         */
        void extractFile(const std::string& t_filename, const std::string& t_path);

        /**
         * @brief Extracts the whole zip archive into the given directory
         * @param t_path The path of the directory to extract to
         */
        void extract(const std::string& t_path);

        /**
         * @brief Returns a list of entries inside the zip file
         * @return A vector containing each entry
         */
        std::vector<ZipEntry> getEntries();

    private:
        /* data */
        std::string m_filename;
    };
} /* m3d */


#endif /* end of include guard: ZIP_H */
