#include <citro3d.h>
#include "m3d/private/graphics.hpp"

namespace m3d {
    namespace priv {
        namespace graphics {
            const C3D_Material material = {
                { 0.1f, 0.1f, 0.1f }, //ambient
                { 0.4f, 0.4f, 0.4f }, //diffuse
                { 0.5f, 0.5f, 0.5f }, //specular0
                { 0.0f, 0.0f, 0.0f }, //specular1
                { 0.0f, 0.0f, 0.0f }, //emission
            };

            const C3D_Mtx materialMatrix =
            {
                {
                    { { 0.0f, 0.2f, 0.2f, 0.2f } }, // Ambient
                    { { 0.0f, 0.4f, 0.4f, 0.4f } }, // Diffuse
                    { { 0.0f, 0.8f, 0.8f, 0.8f } }, // Specular
                    { { 1.0f, 0.0f, 0.0f, 0.0f } }, // Emission
                }
            };
        } /* graphics */
    } /* priv */
} /* m3d */
