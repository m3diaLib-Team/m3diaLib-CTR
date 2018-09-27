#include <citro3d.h>
#include <cstring>
#include "m3d/graphics/drawables/mesh.hpp"

namespace m3d {
    Mesh::Mesh() :
        m_rotationX(0.0f),
        m_rotationY(0.0f),
        m_rotationZ(0.0f),
        m_posX(0.0f),
        m_posY(0.0f),
        m_posZ(0.0f),
        m_scaleX(1.0f),
        m_scaleY(1.0f),
        m_scaleZ(1.0f),
        m_useTexture(false) { /* do nothing */ }

    Mesh::~Mesh() {
        linearFree(m_vbo);
    }

    void Mesh::addPolygon(m3d::Mesh::Polygon t_polygon) {
        m3d::Mesh::Polygon::Vertex vertex0 = t_polygon.getVertex(0),
                                   vertex1 = t_polygon.getVertex(1),
                                   vertex2 = t_polygon.getVertex(2);

        m_vertices.push_back({
            { vertex0.position[0], vertex0.position[1], vertex0.position[2] },
            { vertex0.texcoord[0], vertex0.texcoord[1] },
            { vertex0.normal[0], vertex0.normal[1], vertex0.normal[2] },
        });

        m_vertices.push_back({
            { vertex1.position[0], vertex1.position[1], vertex1.position[2] },
            { vertex1.texcoord[0], vertex1.texcoord[1] },
            { vertex1.normal[0], vertex1.normal[1], vertex1.normal[2] },
        });

        m_vertices.push_back({
            { vertex2.position[0], vertex2.position[1], vertex2.position[2] },
            { vertex2.texcoord[0], vertex2.texcoord[1] },
            { vertex2.normal[0], vertex2.normal[1], vertex2.normal[2] },
        });
    }

    void Mesh::clearVertices() {
        m_vertices.clear();
    }

    void Mesh::setPitch(float t_rotation, bool t_radians) {
        m_rotationX = (t_radians ? t_rotation : C3D_AngleFromDegrees(t_rotation));
    }

    float Mesh::getPitch(bool t_radians) {
        return (t_radians ? m_rotationX : C3D_AngleFromDegrees(m_rotationX));
    }

    void Mesh::setYaw(float t_rotation, bool t_radians) {
        m_rotationY = (t_radians ? t_rotation : C3D_AngleFromDegrees(t_rotation));
    }

    float Mesh::getYaw(bool t_radians) {
        return (t_radians ? m_rotationY : C3D_AngleFromDegrees(m_rotationY));
    }

    void Mesh::setRoll(float t_rotation, bool t_radians) {
        m_rotationZ = (t_radians ? t_rotation : C3D_AngleFromDegrees(t_rotation));
    }

    float Mesh::getRoll(bool t_radians) {
        return (t_radians ? m_rotationZ : C3D_AngleFromDegrees(m_rotationZ));
    }

    void Mesh::setRotation(float t_pitch, float t_yaw, float t_roll, bool t_radians) {
        if (t_radians) {
            m_rotationX = t_pitch;
            m_rotationY = t_yaw;
            m_rotationZ = t_roll;
        } else {
            m_rotationX = C3D_AngleFromDegrees(t_pitch);
            m_rotationY = C3D_AngleFromDegrees(t_yaw);
            m_rotationZ = C3D_AngleFromDegrees(t_roll);
        }
    }

    void Mesh::rotatePitch(float t_delta, bool t_radians) {
        m_rotationX += (t_radians ? t_delta : C3D_AngleFromDegrees(t_delta));
    }

    void Mesh::rotateYaw(float t_delta, bool t_radians) {
        m_rotationY += (t_radians ? t_delta : C3D_AngleFromDegrees(t_delta));
    }

    void Mesh::rotateRoll(float t_delta, bool t_radians) {
        m_rotationZ += (t_radians ? t_delta : C3D_AngleFromDegrees(t_delta));
    }

    void Mesh::setPositionX(float t_position) {
        m_posX = t_position;
    }

    float Mesh::getPositionX() {
        return m_posX;
    }

    void Mesh::setPositionY(float t_position) {
        m_posY = t_position;
    }

    float Mesh::getPositionY() {
        return m_posY;
    }

    void Mesh::setPositionZ(float t_position) {
        m_posZ = t_position;
    }

    float Mesh::getPositionZ() {
        return m_posZ;
    }

    void Mesh::setPosition(float t_positionX, float t_positionY, float t_positionZ) {
        m_posX = t_positionX;
        m_posY = t_positionY;
        m_posZ = t_positionZ;
    }

    void Mesh::setPosition(m3d::Vector3f t_position) {
        m_posX = t_position.x;
        m_posY = t_position.y;
        m_posZ = t_position.z;
    }

    void Mesh::moveX(float t_delta) {
        m_posX += t_delta;
    }

    void Mesh::moveY(float t_delta) {
        m_posY += t_delta;
    }

    void Mesh::moveZ(float t_delta) {
        m_posZ += t_delta;
    }

    void Mesh::setScaleX(float t_scale) {
        m_scaleX = t_scale;
    }

    float Mesh::getScaleX() {
        return m_scaleX;
    }

    void Mesh::setScaleY(float t_scale) {
        m_scaleY = t_scale;
    }

    float Mesh::getScaleY() {
        return m_scaleY;
    }

    void Mesh::setScaleZ(float t_scale) {
        m_scaleZ = t_scale;
    }

    float Mesh::getScaleZ() {
        return m_scaleZ;
    }

    void Mesh::setScale(float t_scaleX, float t_scaleY, float t_scaleZ) {
        m_scaleX = t_scaleX;
        m_scaleY = t_scaleY;
        m_scaleZ = t_scaleZ;
    }

    void Mesh::scaleX(float t_delta) {
        m_scaleX += t_delta;
    }

    void Mesh::scaleY(float t_delta) {
        m_scaleY += t_delta;
    }

    void Mesh::scaleZ(float t_delta) {
        m_scaleZ += t_delta;
    }

    void Mesh::setMaterial(m3d::Material& t_material) {
        m_material = t_material;
    }

    m3d::Material& Mesh::getMaterial() {
        return m_material;
    }

    void Mesh::bindTexture(m3d::Texture& t_texture, bool t_resetMaterial) {
        m_useTexture = true;
        m_texture = t_texture;

        if (t_resetMaterial) {
            m_material.setAmbient(125, 125, 125);
            m_material.setDiffuse(255, 255, 255);
        }
    }

    void Mesh::unbindTexture(bool t_resetMaterial) {
        m_useTexture = false;

        if (t_resetMaterial) {
            m_material = m3d::Material();
        }
    }

    m3d::Texture& Mesh::getTexture() {
        return m_texture;
    }

    bool Mesh::isTextureBound() {
        return m_useTexture;
    }

    void Mesh::draw(m3d::RenderContext t_context) {
        if (t_context.getMode() == m3d::RenderContext::Mode::Spatial) {
            // manipulate modelview matrix
            Mtx_Identity(&t_context.getModelMatrix());
            Mtx_Translate(&t_context.getModelMatrix(), m_posX, m_posY,  -1.87 - m_posZ, true);
            Mtx_RotateX(&t_context.getModelMatrix(), m_rotationX, true);
            Mtx_RotateY(&t_context.getModelMatrix(), m_rotationY, true);
            Mtx_RotateZ(&t_context.getModelMatrix(), m_rotationZ, true);
            Mtx_Scale(&t_context.getModelMatrix(), m_scaleX, m_scaleY, m_scaleZ);

            // set material
            C3D_LightEnvMaterial(&t_context.getLightEnvironment(), m_material.getMaterial());

            if (m_useTexture) {
                // enable textures
                t_context.enableTextures(true);

                // bind the texture
                C3D_TexSetFilter(m_texture.getTexture(), GPU_LINEAR, GPU_LINEAR);
                C3D_TexBind(0, m_texture.getTexture());
            } else {
                // disable textures
                t_context.enableTextures(false);
            }

            // create buffer
            C3D_BufInfo* bufInfo = C3D_GetBufInfo();
            BufInfo_Init(bufInfo);
            BufInfo_Add(bufInfo, m_vbo, sizeof(m3d::Mesh::Polygon::Vertex), 3, 0x210);

            // update the uniforms
            C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, t_context.getModelUniform(),  &t_context.getModelMatrix());

            // draw the VBO
            C3D_DrawArrays(GPU_TRIANGLES, 0, m_vertices.size());
        }
    }

    // protected methods
    void Mesh::updateVBO() {
        linearFree(m_vbo);
        m_vbo = static_cast<m3d::Mesh::Polygon::Vertex*>(linearAlloc(m_vertices.size() * sizeof(m3d::Mesh::Polygon::Vertex)));

        for (unsigned int i = 0; i < m_vertices.size(); i++) {
            float x = m_vertices[i].position[0],
                  y = m_vertices[i].position[1],
                  z = m_vertices[i].position[2],
                  u = m_vertices[i].texcoord[0],
                  v = m_vertices[i].texcoord[1],
                 nx = m_vertices[i].normal[0],
                 ny = m_vertices[i].normal[1],
                 nz = m_vertices[i].normal[2];

            m_vbo[i] = (m3d::Mesh::Polygon::Vertex) { { x, y, z }, { u, v }, { nx, ny, nz } };
        }
    }
} /* m3d */
