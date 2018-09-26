#include "m3d/graphics/drawables/meshes/model.hpp"
#include "m3d/private/OBJ_Loader.h"

namespace m3d {
        bool Model::loadFromFile(const std::string& t_filename) {
            objl::Loader loader;

            if(!loader.LoadFile(t_filename)) {
                return false;
            }

            for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++) {
                objl::Mesh curMesh = loader.LoadedMeshes[i];

                for (unsigned int j = 0; j < curMesh.Vertices.size() - 2; j += 3) {
                    addPolygon(m3d::Mesh::Polygon(
                        { {
                            curMesh.Vertices[j].Position.X,
                            curMesh.Vertices[j].Position.Y,
                            curMesh.Vertices[j].Position.Z
                        }, {
                            curMesh.Vertices[j].TextureCoordinate.X,
                            curMesh.Vertices[j].TextureCoordinate.Y
                        }, {
                            curMesh.Vertices[j].Normal.X,
                            curMesh.Vertices[j].Normal.Y,
                            curMesh.Vertices[j].Normal.Z
                        } },

                        { {
                            curMesh.Vertices[j + 1].Position.X,
                            curMesh.Vertices[j + 1].Position.Y,
                            curMesh.Vertices[j + 1].Position.Z
                        }, {
                            curMesh.Vertices[j + 1].TextureCoordinate.X,
                            curMesh.Vertices[j + 1].TextureCoordinate.Y
                        }, {
                            curMesh.Vertices[j + 1].Normal.X,
                            curMesh.Vertices[j + 1].Normal.Y,
                            curMesh.Vertices[j + 1].Normal.Z
                        } },

                        { {
                            curMesh.Vertices[j + 2].Position.X,
                            curMesh.Vertices[j + 2].Position.Y,
                            curMesh.Vertices[j + 2].Position.Z
                        }, {
                            curMesh.Vertices[j + 2].TextureCoordinate.X,
                            curMesh.Vertices[j + 2].TextureCoordinate.Y
                        }, {
                            curMesh.Vertices[j + 2].Normal.X,
                            curMesh.Vertices[j + 2].Normal.Y,
                            curMesh.Vertices[j + 2].Normal.Z
                        } }
                    ));
                }
            }

            updateVbo();

            return true;
        }
} /* m3d */
