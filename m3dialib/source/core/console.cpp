#include <3ds.h>
#include <stdio.h>
#include "m3d/core/console.hpp"
#include "m3d/private/core.hpp"

namespace m3d {
    const char* Console::m_codeLUT[] = {
            "\x1b[30;1m", // BlackFG
            "\x1b[31;1m", // RedFG
            "\x1b[32;1m", // GreenFG
            "\x1b[33;1m", // YellowFG
            "\x1b[34;1m", // BlueFG
            "\x1b[35;1m", // MagentaFG
            "\x1b[36;1m", // CyanFG
            "\x1b[37;1m", // WhiteFG

            "\x1b[40;1m", // BlackBG
            "\x1b[41;1m", // RedBG
            "\x1b[42;1m", // GreenBG
            "\x1b[43;1m", // YellowBG
            "\x1b[44;1m", // BlueBG
            "\x1b[45;1m", // MagentaBG
            "\x1b[46;1m", // CyanBG
            "\x1b[47;1m", // WhiteBG

            "\x1b[1m", // Bold
            "\x1b[2m", // Faint
            "\x1b[4m", // Underline
            "\x1b[9m", // Strikethrough

            "\x1b[0m",  // Reset
            "\n"        // Endl
    };

    Console::Console() {

    }

    Console::Console(m3d::RenderContext::RenderTarget t_screen) {
        Console::useScreen(t_screen);
    }

    const std::string Console::useScreen(m3d::RenderContext::RenderTarget t_target) {
        switch(t_target) {
            case m3d::RenderContext::RenderTarget::Top:
                m3d::priv::core::consoleTop = true;
                consoleInit(GFX_TOP, &m_console);
                break;
            case m3d::RenderContext::RenderTarget::Bottom:
                m3d::priv::core::consoleBottom = true;
                consoleInit(GFX_BOTTOM, &m_console);
                break;
            default:
                m3d::priv::core::consoleTop = true;
                consoleInit(GFX_TOP, &m_console);
                break;
        }

        return "";
    }

    void Console::clear() {
        consoleClear();
    }

    void Console::setWindow(m3d::Console::Window t_window) {
        consoleSetWindow(&m_console, t_window.x, t_window.y, t_window.width, t_window.height);
    }

    m3d::Console& Console::operator<<(const std::string& t_string) {
        consoleSelect(&m_console);
        printf(t_string.c_str());
        return *this;
    }

    m3d::Console& Console::operator<<(m3d::Console::ConsoleCode t_char) {
        consoleSelect(&m_console);
        printf(m_codeLUT[(int) t_char]);
        return *this;
    }

    void m3d::Console::print(const std::string& t_string) {
        *this << t_string;
    }

    void m3d::Console::println(const std::string& t_string) {
        *this << t_string << m3d::Console::Endl;
    }

    void m3d::Console::printAt(int t_x, int t_y, const std::string& t_string) {
        *this << Console::position(t_x, t_y) << t_string << m3d::Console::Endl;
    }
}
