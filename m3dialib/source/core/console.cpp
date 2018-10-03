#include <3ds.h>
#include <stdio.h>
#include "m3d/core/console.hpp"
#include "m3d/private/core.hpp"

namespace m3d {
    const char* Console::m_codeLUT[] = {
            "\x1b[31m",
            "\x1b[32m",
            "\x1b[33m",
            "\x1b[34m",
            "\x1b[35m",
            "\x1b[36m",
            "\x1b[0m",
            "\n"
    };

    void Console::enableConsole(m3d::RenderContext::ScreenTarget t_target) {
        if (t_target == m3d::RenderContext::ScreenTarget::Top) {
            m3d::priv::core::consoleTop = true;
        } else {
            m3d::priv::core::consoleBottom = true;
        }
    }

    void Console::disableConsole(m3d::RenderContext::ScreenTarget t_target) {
        if (t_target == m3d::RenderContext::ScreenTarget::Top) {
            m3d::priv::core::consoleTop = false;
        } else {
            m3d::priv::core::consoleBottom = false;
        }
    }

    m3d::Console& Console::operator<<(const std::string& t_string) {
        printf(t_string.c_str());
        return *this;
    }

    m3d::Console& Console::operator<<(m3d::Console::ConsoleCode t_char) {
        printf(m_codeLUT[(int) t_char]);
        return *this;
    }
}
