/**
 * @file m3dia.hpp
 * @brief The master header which includes all other files from the library
 */
#pragma once

// 3ds libraries
#include <citro2d.h>

// m3Dia includes
#include "m3d/audio/audio.hpp"
#include "m3d/core/core.hpp"
#include "m3d/graphics/graphics.hpp"
#include "m3d/input/input.hpp"
#include "m3d/networking/networking.hpp"
#include "m3d/utils/utils.hpp"

#ifdef M3D_DEBUG
#include <iostream>
/**
 * @brief Breaks the execution and waits for the A-button to be pressed
 *
 * To activate, define M3D_DEBUG before including this file
 */
#define M3D_BREAKPOINT() \
        std::cout << "\u001b[33;1mBreakpoint reached: \n" << (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << ":" << __LINE__ << "\u001b[0m\n"; \
        while (true) { hidScanInput(); if (m3d::Input::buttonPressed(m3d::Input::Button::A)) break; }

/**
 * @brief Breaks the execution and waits for the A-button to be pressed
 * @param  msg A message to display
 *
 * To activate, define M3D_DEBUG before including this file
 */
#define M3D_DEBUGPOINT(msg) \
    std::cout << "\u001b[33;1mBreakpoint reached: \n" << (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << ":" << __LINE__ << ": " << msg << "\u001b[0m\n"; \
    while (true) { hidScanInput(); if (m3d::Input::buttonPressed(m3d::Input::Button::A)) break; }
#else
#define M3D_BREAKPOINT()
#define M3D_DEBUGPOINT(msg)
#endif
