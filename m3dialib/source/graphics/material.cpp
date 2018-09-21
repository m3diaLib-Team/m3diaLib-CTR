#include "m3d/graphics/material.hpp"

namespace m3d {
    Material::Material() :
        m_ambient(51, 51, 51),
        m_diffuse(102, 102, 102),
        m_specular0(127, 127, 127) {
            m_material = new C3D_Material;
            updateMaterial();
        }

    Material::Material(C3D_Material t_material) {
        setMaterial(t_material);
        updateMaterial();
    }

    Material::~Material() {
        delete m_material;
    }

    void Material::setMaterial(C3D_Material t_material) {
        m_ambient.setColor(t_material.ambient[2], t_material.ambient[1], t_material.ambient[0]);
        m_diffuse.setColor(t_material.diffuse[2], t_material.diffuse[1], t_material.diffuse[0]);
        m_specular0.setColor(t_material.specular0[2], t_material.specular0[1], t_material.specular0[0]);
        m_specular1.setColor(t_material.specular1[2], t_material.specular1[1], t_material.specular1[0]);
        m_emission.setColor(t_material.emission[2], t_material.emission[1], t_material.emission[0]);

        updateMaterial();
    }

    C3D_Material* Material::getMaterial() const {
        return m_material;
    }

    void Material::setAmbient(m3d::Color t_color) {
        m_ambient = t_color;
        updateMaterial();
    }

    void Material::setAmbient(float t_r, float t_g, float t_b) {
        m_ambient = m3d::Color(t_r * 255, t_g * 255, t_b * 255);
        updateMaterial();
    }

    m3d::Color Material::getAmbient() {
        return m_ambient;
    }

    void Material::setDiffuse(m3d::Color t_color) {
        m_diffuse = t_color;
        updateMaterial();
    }

    void Material::setDiffuse(float t_r, float t_g, float t_b) {
        m_diffuse = m3d::Color(t_r * 255, t_g * 255, t_b * 255);
        updateMaterial();
    }

    m3d::Color Material::getDiffuse() {
        return m_diffuse;
    }

    void Material::setSpecular0(m3d::Color t_color) {
        m_specular0 = t_color;
        updateMaterial();
    }

    void Material::setSpecular0(float t_r, float t_g, float t_b) {
        m_specular0 = m3d::Color(t_r * 255, t_g * 255, t_b * 255);
        updateMaterial();
    }

    m3d::Color Material::getSpecular0() {
        return m_specular0;
    }

    void Material::setSpecular1(m3d::Color t_color) {
        m_specular1 = t_color;
        updateMaterial();
    }

    void Material::setSpecular1(float t_r, float t_g, float t_b) {
        m_specular1 = m3d::Color(t_r * 255, t_g * 255, t_b * 255);
        updateMaterial();
    }

    m3d::Color Material::getSpecular1() {
        return m_specular1;
    }

    void Material::setEmission(m3d::Color t_color) {
        m_emission = t_color;
        updateMaterial();
    }

    void Material::setEmission(float t_r, float t_g, float t_b) {
        m_emission = m3d::Color(t_r * 255, t_g * 255, t_b * 255);
        updateMaterial();
    }

    m3d::Color Material::getEmission() {
        return m_emission;
    }

    // private methods
    void Material::updateMaterial() {
        m_material->ambient[0] = (float) m_ambient.getBlue() / 255;
        m_material->ambient[1] = (float) m_ambient.getGreen() / 255;
        m_material->ambient[2] = (float) m_ambient.getRed() / 255;

        m_material->diffuse[0] = (float) m_diffuse.getBlue() / 255;
        m_material->diffuse[1] = (float) m_diffuse.getGreen() / 255;
        m_material->diffuse[2] = (float) m_diffuse.getRed() / 255;

        m_material->specular0[0] = (float) m_specular0.getBlue() / 255;
        m_material->specular0[1] = (float) m_specular0.getGreen() / 255;
        m_material->specular0[2] = (float) m_specular0.getRed() / 255;

        m_material->specular1[0] = (float) m_specular1.getBlue() / 255;
        m_material->specular1[1] = (float) m_specular1.getGreen() / 255;
        m_material->specular1[2] = (float) m_specular1.getRed() / 255;

        m_material->emission[0] = (float) m_emission.getBlue() / 255;
        m_material->emission[0] = (float) m_emission.getGreen() / 255;
        m_material->emission[0] = (float) m_emission.getRed() / 255;
    }
} /* m3d */
