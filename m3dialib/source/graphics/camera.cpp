#include <cmath>
#include "m3d/graphics/camera.hpp"

namespace m3d {
    Camera::Camera() :
        m_posX(0.0f),
        m_posY(0.0f),
        m_posZ(0.0f),
        m_rotationX(0.0f),
        m_rotationY(0.0f),
        m_rotationZ(0.0f) { /* do nothing */ }

    void Camera::setRotationX(float t_rotation) {
        m_rotationX = t_rotation;
    }

    float Camera::getRotationX() {
        return m_rotationX;
    }

    void Camera::setRotationY(float t_rotation) {
        m_rotationY = t_rotation;
    }

    float Camera::getRotationY() {
        return m_rotationY;
    }

    void Camera::setRotationZ(float t_rotation) {
        m_rotationZ = t_rotation;
    }

    float Camera::getRotationZ() {
        return m_rotationZ;
    }

    void Camera::setRotation(float t_rotationX, float t_rotationY, float t_rotationZ) {
        m_rotationX = t_rotationX;
        m_rotationY = t_rotationY;
        m_rotationZ = t_rotationZ;
    }

    void Camera::rotateX(float t_delta) {
        m_rotationX += t_delta;
    }

    void Camera::rotateY(float t_delta) {
        m_rotationY += t_delta;
    }

    void Camera::rotateZ(float t_delta) {
        m_rotationZ += t_delta;
    }

    void Camera::setPositionX(float t_position) {
        m_posX = t_position;
    }

    float Camera::getPositionX() {
        return m_posX;
    }

    void Camera::setPositionY(float t_position) {
        m_posY = t_position;
    }

    float Camera::getPositionY() {
        return m_posY;
    }

    void Camera::setPositionZ(float t_position) {
        m_posZ = t_position;
    }

    float Camera::getPositionZ() {
        return m_posZ;
    }

    void Camera::setPosition(float t_positionX, float t_positionY, float t_positionZ) {
        m_posX = t_positionX;
        m_posY = t_positionY;
        m_posZ = t_positionZ;
    }

    void Camera::setPosition(m3d::Vector3f t_position) {
        m_posX = t_position.x;
        m_posY = t_position.y;
        m_posZ = t_position.z;
    }

    void Camera::moveX(float t_delta) {
        m_posX += t_delta;
    }

    void Camera::moveY(float t_delta) {
        m_posY += t_delta;
    }

    void Camera::moveZ(float t_delta) {
        m_posZ += t_delta;
    }

    C3D_Mtx& Camera::getViewMatrix() {
        Mtx_Identity(&m_view);
        Mtx_RotateX(&m_view, m_rotationX, true);
        Mtx_RotateY(&m_view, m_rotationY, true);
        Mtx_RotateZ(&m_view, m_rotationZ, true);
        Mtx_Translate(&m_view, -m_posX, m_posY, -m_posZ, true);

        return m_view;
    }
} /* m3d */
