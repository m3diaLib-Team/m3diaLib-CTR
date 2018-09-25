# m3diaLib [![Build Status](https://travis-ci.org/StuntHacks/m3diaLib.svg?branch=master)](https://travis-ci.org/StuntHacks/m3diaLib)
A fast, extensive and powerful allround media and game library for the Nintendo 3DS, written in C++.

#### Click [here](#installation) to get to the installation instructions.

#### This library is still in beta! If you have any issues or find any bugs, please report them!

## Features
The m3diaLib (spelled media-lib) is split into multiple modules, which can then be split into smaller parts:

### Core
The core module contains all functionality for interacting with the system. Its features range from running and handling the app itself to displaying errors and running system applets.

**Its main features are:**
 * A class for running your homebrew app
 * Easy interaction with the system itself
 * Starting and running applets
 * Time measurement
 * Support for the RomFS
 * Multithreading and concurrency

### Input
The input module does what its name says: It handles each and every input for interacting with the user.

**Its main features are:**
 * Handling button input
 * Handling touch input

### Graphics
The graphics module is by far the biggest module. It handles anything graphic-wise, from rendering simple shapes to rendering and animating high-quality textures.

**Its main features are:**
 * Support for the top and bottom screen
 * Support for stereoscopic 3D
 * Easy-to-use interface for fast rendering on both screens
 * Support for transformation of textures and sprites
 * Pre-coded shapes as well as a shape class for easily rendering your own shapes
 * Easy-to-use color system
 * Collision detection

### Audio
The audio module can be used for both music and sound effects.

**Its main features are:**
 * Loading or streaming audio files directly from the file system
 * **Support for .wav and .mp3 (more to come!)**
 * Two different classes, sound and music, which have features that can be helpful specific in their use case

### Utils
The utils module contains all kind of useful utilities. Some of its functionalities are the following:

 * Basic encryption

---

All features are well documented [here](https://docs.stunthacks.eu/m3dialib/). Examples can be viewed [here](https://github.com/StuntHacks/m3d-examples).

## How to use it
The barebones of a homebrew app using the m3diaLib would look like this:

```cpp
#include <m3dia.hpp>

int main() {
    m3d::Applet app;

    while (app.isRunning()) {
        if (m3d::buttons::buttonPressed(m3d::buttons::Button::Start)) {
            app.exit(); // exit if start is pressed
        }
    }
}
```
Easy, isn't it?

## Planned features:
#### Audio:
 * Microphone support
 * More file formats

#### Core:
 * Support for all availiable os and system functionality

#### Graphics:
 * Animation
 * RenderTargets
 * More file formats for textures
 * 3D support

#### Networking:

This module isn't availiable at the moment. However, it's planned features are:
 * A simple HTTP and WebSocket client and server
 * Socket support
 * A 3DS-download-game alternative (more on that at a later point)

#### Utils:
 * ZIP compression and decompression
 * JSON and XML parsing
 * Secure random numbers

...and anything that strikes my mind in the future.

## Installation
To install the library, download the latest release and then execute the following commands:

```
make
make install
```

## Dependencies
To compile a m3diaLib-app, you need the following dependencies installed (install via [devkitPro-pacman](https://devkitpro.org/wiki/devkitPro_pacman)):
 * libctru
 * citro3d
 * citro2d
 * 3ds-tinyxml2
 * 3ds-zlib
 * 3ds-mpg123
 * 3ds-libpng
 * 3ds-freetype
 * tex3ds (if you want to use spritesheets)

## Credits
 * [ctrulib](https://github.com/smealum/ctrulib/)
 * [citro3d](https://github.com/fincs/citro3d) (zLib)
 * [citro2d](https://github.com/devkitPro/citro2d) (zLib)
 * [OBJ-Loader](https://github.com/Bly7/OBJ-Loader) (MIT)
