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

    void Camera::setPitch(float t_rotation, bool t_radians) {
        m_rotationX = (t_radians ? t_rotation : C3D_AngleFromDegrees(t_rotation));
    }

    float Camera::getPitch(bool t_radians) {
        return (t_radians ? m_rotationX : C3D_AngleFromDegrees(m_rotationX));
    }

    void Camera::setYaw(float t_rotation, bool t_radians) {
        m_rotationY = (t_radians ? t_rotation : C3D_AngleFromDegrees(t_rotation));
    }

    float Camera::getYaw(bool t_radians) {
        return (t_radians ? m_rotationY : C3D_AngleFromDegrees(m_rotationY));
    }

    void Camera::setRoll(float t_rotation, bool t_radians) {
        m_rotationZ = (t_radians ? t_rotation : C3D_AngleFromDegrees(t_rotation));
    }

    float Camera::getRoll(bool t_radians) {
        return (t_radians ? m_rotationZ : C3D_AngleFromDegrees(m_rotationZ));
    }

    void Camera::setRotation(float t_pitch, float t_yaw, float t_roll, bool t_radians) {
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

    void Camera::rotatePitch(float t_delta, bool t_radians) {
        m_rotationX += (t_radians ? t_delta : C3D_AngleFromDegrees(t_delta));
    }

    void Camera::rotateYaw(float t_delta, bool t_radians) {
        m_rotationY += (t_radians ? t_delta : C3D_AngleFromDegrees(t_delta));
    }

    void Camera::rotateRoll(float t_delta, bool t_radians) {
        m_rotationZ += (t_radians ? t_delta : C3D_AngleFromDegrees(t_delta));
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
        Mtx_Translate(&m_view, m_posX, m_posY, m_posZ, true);

        return m_view;
    }
} /* m3d */
