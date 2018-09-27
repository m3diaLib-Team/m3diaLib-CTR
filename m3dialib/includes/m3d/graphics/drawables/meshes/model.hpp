/**
 * @file model.hpp
 * @brief Defines the Model-class which allows for loading 3D models
 */
#ifndef MODEL_H
#define MODEL_H

#pragma once
#include "m3d/graphics/drawables/mesh.hpp"

namespace m3d {
    /**
     * @brief The Model-class
     */
    class Model: public m3d::Mesh {
    public:
        /**
         * @brief Loads a model from a file (currently .obj-only)
         * @param  t_filename The path to the file
         * @return            `true` if loading was successful, `false` otherwise
         * @warning Keep in mind, that your model needs to be triangulated in order to load correctly. An option to automatically triangulate will be added in the future however it will still be faster to triangulate them before-hand.
         */
        bool loadFromFile(const std::string& t_filename);
    };
} /* m3d */


#endif /* end of include guard: MODEL_H */
