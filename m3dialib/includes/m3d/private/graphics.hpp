#ifndef GRAPHICS_PRIVATE_H
#define GRAPHICS_PRIVATE_H

#pragma once
#include <3ds.h>

namespace m3d {
    class Camera;

    namespace priv {
        namespace graphics {
            struct Vertex {
                float pos[3];
                float texcoord[2];
                float normals[3];
                float blend[2];
                u32 color;
            };

            extern m3d::Camera defaultCamera0, defaultCamera1;
            extern Vertex *vertexBuffer2d, *vertexBuffer3d;
        } /* graphics */
    } /* priv */
} /* m3d */


#endif /* end of include guard: GRAPHICS_PRIVATE_H */
