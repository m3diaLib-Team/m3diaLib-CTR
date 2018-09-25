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
        bool loadFromFile(const std::string& t_filename);
    };
} /* m3d */


#endif /* end of include guard: MODEL_H */
