#ifndef CONSOLE_H
#define CONSOLE_H

#include <3ds.h>

namespace m3d {
    class Console {
        public:
            enum class ConsoleColor : const char {
                RED     = *"\x1b[31m",
                GREEN   = *"\x1b[32m",
                YELLOW  = *"\x1b[33m",
                BLUE    = *"\x1b[34m",
                MAGENTA = *"\x1b[35m",
                CYAN    = *"\x1b[36m",
                RESET   = *"\x1b[0m"
            };

            void print(const char* t_data);
            void print(const char* t_data, ConsoleColor t_color);

            void println(const char* t_data);
            void println(const char* t_data, ConsoleColor t_color);
    };
}

#endif