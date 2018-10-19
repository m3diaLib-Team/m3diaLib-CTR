/**
 * @file console.hpp
 * @brief Defines the Console-class
 */
#ifndef CONSOLE_H
#define CONSOLE_H

#pragma once

#include <3ds.h>
#include <string>
#include "m3d/graphics/renderContext.hpp"

namespace m3d {
    /**
     * @brief The Console-class, used for printing text
     */
    class Console {
        public:
            #define MAX_TOP_WIDTH 50
            #define MAX_TOP_HEIGHT 30
            // gotta use an old-school enum so that one can use `m3d::Console::Red`
            /**
             * @brief Different control characters for usage in streams
             */
            enum ConsoleCode {
                BlackFG = 0,   ///< Black text
                RedFG,         ///< Red text
                GreenFG,       ///< Green text
                YellowFG,      ///< Yellow text
                BlueFG,        ///< Blue text
                MagentaFG,     ///< Magenta text
                CyanFG,        ///< Cyan text
                WhiteFG,       ///< White text

                BlackBG,       ///< Black background
                RedBG,         ///< Red background
                GreenBG,       ///< Green background
                YellowBG,      ///< Yellow background
                BlueBG,        ///< Blue background
                MagentaBG,     ///< Magenta background
                CyanBG,        ///< Cyan background
                WhiteBG,       ///< White background

                Bold,          ///< Bold text (default)
                Faint,         ///< Faint text
                Underline,     ///< Underlined text
                Strikethrough, ///< Strikethrough

                Reset,         ///< Resets all formatting
                Endl           ///< Ends the line and starts a new one
            };

            struct Window {
                int x;
                int y;
                int width;
                int height;
            };

            /**
             * @brief Default constructor
             */
            Console();

            Console(m3d::RenderContext::RenderTarget t_screen);

            /**
             * @brief Returns the escape code to position the text at the given position
             * @param  t_x The x-position
             * @param  t_y The y-position
             * @return     The generated escape code
             * @note This is intended to be used in streams
             * @note Positions are measured in cells, not pixels
             */
            static inline const std::string position(int t_x, int t_y) {
                return "\x1b[" + std::to_string(t_y) + ";" + std::to_string(t_x) + "H";
            }

            void print(const std::string& t_data);

            void println(const std::string& t_data);

            void printAt(int t_x, int t_y, const std::string& t_data);

            /**
             * @brief Tells the console which screen to draw on
             * @param  t_target The screen target
             * @return          An empty string. This is to make it possible to use this method in streams
             * @warning Once a screen was used for the console, it can't be used for normal rendering again
             */
            const std::string useScreen(m3d::RenderContext::RenderTarget t_target);
            void clear();

            /**
             * @brief Sets the window for the console to use
             * @param t_x      The x-position of the window
             * @param t_y      The y-position of the window
             * @param t_width  The width of the window
             * @param t_height The height of the window
             * @note Positions are measured in cells, not pixels
             */
            void setWindow(Window t_window);

            /**
             * @brief Overloads the streaming operator
             */
            m3d::Console& operator<<(const std::string& t_string);

            /**
             * @brief Overloads the streaming operator
             */
            m3d::Console& operator<<(m3d::Console::ConsoleCode t_char);

        private:
            PrintConsole m_console;
            static const char* m_codeLUT[];
    };
}

#endif
