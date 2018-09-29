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
        while (true) { hidScanInput(); if (m3d::buttons::buttonPressed(m3d::buttons::Button::A)) break; }

/**
 * @brief Breaks the execution and waits for the A-button to be pressed
 * @param  msg A message to display
 *
 * To activate, define M3D_DEBUG before including this file
 */
#define M3D_DEBUGPOINT(msg) \
    std::cout << "\u001b[33;1mBreakpoint reached: \n" << (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << ":" << __LINE__ << ": " << msg << "\u001b[0m\n"; \
    while (true) { hidScanInput(); if (m3d::buttons::buttonPressed(m3d::buttons::Button::A)) break; }
#else
#define M3D_BREAKPOINT()
#define M3D_DEBUGPOINT(msg)
#endif

/**
 * @brief The current major version of the library
 */
#define M3D_VERSION_MAJOR 0

/**
 * @brief The current minor version of the library
 */
#define M3D_VERSION_MINOR 2

/**
 * @brief The current revision of the library
 */
#define M3D_VERSION_REVISION 1

/**
 * @brief The current version of the library in the format MAJOR.MINOR.REVISION
 */
#define M3D_VERSION M3D_VERSION_MAJOR + "." + M3D_VERSION_MINOR + "." + M3D_VERSION_REVISION
