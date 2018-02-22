# m3diaLib
A fast, extensive and powerful allround media and game library for the Nintendo 3DS, written in C++.

## Features
The m3diaLib (spelled media-lib) is split into 4 big modules, which can then be split into smaller parts:

### Core
The core module contains all functionality for interacting with the system. It's features range from running and handling the app itself to displaying errors and running system applets.

**It's main features are:**
 * A class for running your homebrew app
 * Easy interaction with the system itself
 * Starting and running applets
 * Support for the RomFS

### Input
The input module does what it's name says: It handles each and every input for interacting with the user.

**It's main features are:**
 * Handling button input
 * Handling touch input
 * Using the built-in software keyboard (no need to code one yourself anymore!)

### Graphics
The graphics module is by far the biggest module. It handles anything graphic-wise, from rendering simple shapes to rendering and animating high-quality textures.

**It's main features are:**
 * Support for the top and bottom screen
 * Support for stereoscopic 3D
 * Easy, yet advanced, interface for fast and powerful rendering on both screens
 * **Support for high-quality textures and being able to load them directly from the file system**
 * Support for transformation of textures and sprites
 * Pre-coded shapes as well as a shape class for easily rendering your own shapes
 * Easy to use color system
 * Support for render targets
 * Collision detection

### Audio
The audio module can be used for both music and sound effects.

**It's main features are:**
 * Loading or streaming audio files directly from the file system
 * **Support for .ogg and .mp3 (more to come!)**
 * Two different classes, sound and music, which have features that can be helpful specific in their use case

### Networking
You want to interact with a game server? You want to download updates on the fly? Then this is the right module for you!

**It's main features are:**
 * A simple http and websocket client
 * **My LWMP protocol, for easily implementing a local multiplayer mode (see section below)**

All features are well documented and come with at least one example. If you still have questions, you can post an issue and I will be happy to help! :) In addition to that, a detailed tutorial will come soon.

## How to use it
The barebones of a homebrew app using the m3diaLib would look like this:

```cpp
#include <m3dia.hpp>

int main() {
    m3d::Applet app;

    while (app.isRunning()) {
        if (m3d::buttons::buttonPressed(m3d::buttons::BUTTON_START)) {
            app.exit(); // exit if start is pressed
        }
    }
}
```
Easy, isn't it?

## The LWMP protocol
The ability of the 3DS to host game servers and join them on the go (also called local multiplayer), is awesome - it can be extremely funny to have some friends over, each of them staring on their own screen while battling each other in Mario Kart.

Sadly, we are not able to make use of that feature. To compensate that, I created a new protocol: the LWMP (local wifi multiplayer) protocol! It's a complete alternative for local multiplayer games, works over the local wifi and even has some advantages over Nintendo's solution:
 * Virtually no distance limitation - the only limitation is that users have to be on the same network
 * Rijndael encryption

Other features inclue:
 * Easily create a local server or join one in your local network, without having to write too much code
 * Manage all connections easily and send data to them directly or via a broadcast

For more information, please refer to the documentation!

## TO-DO
 * [ ] Add more code examples to readme
 * [ ] Add examples to documentation
 * [ ] Add support for more audio formats

## Credits
 * Smealum and everyone who worked with him for the [ctrulib](https://github.com/smealum/ctrulib/)
 * fincs for [citro3d](https://github.com/fincs/citro3d)
