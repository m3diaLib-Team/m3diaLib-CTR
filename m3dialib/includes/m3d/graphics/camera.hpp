/**
 * @file camera.hpp
 * @brief Defines the Camera-class
 */
#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include <citro3d.h>
#include "vertex.hpp"

namespace m3d {
    class Camera {
    public:
        /**
         * @brief Default constructor
         */
        Camera();

        /**
         * @brief Sets the rotation on the X-axis
         * @param t_rotation The absolute rotation
         */
        void setPitch(float t_rotation);

        /**
         * @brief Returns the rotation on the X-axis
         * @return The absolute rotation
         */
        float getPitch();

        /**
         * @brief Sets the rotation on the Y-axis
         * @param t_rotation The absolute rotation
         */
        void setYaw(float t_rotation);

        /**
         * @brief Returns the rotation on the Y-axis
         * @return The absolute rotation
         */
        float getYaw();

        /**
         * @brief Sets the rotation on the Z-axis
         * @param t_rotation The absolute rotation
         */
        void setRoll(float t_rotation);

        /**
         * @brief Returns the rotation on the /-axis
         * @return The absolute rotation
         */
        float getRoll();

        /**
         * @brief Sets the rotation of the camera
         * @param t_pitch The rotation on the X-axis
         * @param t_yaw   The rotation on the Y-axis
         * @param t_roll  The rotation on the Z-axis
         */
        void setRotation(float t_pitch, float t_yaw, float t_roll);

        /**
         * @brief Rotates the camera a given amount on the X-axis
         * @param t_delta The amount to rotate
         */
        void rotatePitch(float t_delta);

        /**
         * @brief Rotates the camera a given amount on the Y-axis
         * @param t_delta The amount to rotate
         */
        void rotateYaw(float t_delta);

        /**
         * @brief Rotates the camera a given amount on the Z-axis
         * @param t_delta The amount to rotate
         */
        void rotateRoll(float t_delta);

        /**
         * @brief Sets the position on the X-axis
         * @param t_position The absolute position
         */
        void setPositionX(float t_position);

        /**
         * @brief Returns the current position on the X-axis
         * @return The absolute position
         */
        float getPositionX();

        /**
         * @brief Sets the position on the Y-axis
         * @param t_position The absolute position
         */
        void setPositionY(float t_position);

        /**
         * @brief Returns the current position on the Y-axis
         * @return The absolute position
         */
        float getPositionY();

        /**
         * @brief Sets the position on the Z-axis
         * @param t_position The absolute position
         */
        void setPositionZ(float t_position);

        /**
         * @brief Returns the current position on the Z-axis
         * @return The absolute position
         */
        float getPositionZ();

        /**
         * @brief Sets the position of the camera
         * @param t_positionX The position on the X-axis
         * @param t_positionY The position on the Y-axis
         * @param t_positionZ The position on the Z-axis
         */
        void setPosition(float t_positionX, float t_positionY, float t_positionZ);

        /**
         * @brief Sets the position of the camera
         * @param t_position The absolute position, represented as a vector
         */
        void setPosition(m3d::Vector3f t_position);

        /**
         * @brief Moves the camera along the X-axis
         * @param t_delta The amount to move
         */
        void moveX(float t_delta);

        /**
         * @brief Moves the camera along the Y-axis
         * @param t_delta The amount to move
         */
        void moveY(float t_delta);

        /**
         * @brief Moves the camera along the Z-axis
         * @param t_delta The amount to move
         */
        void moveZ(float t_delta);

        void moveSideways(float t_delta);

        void moveForward(float t_delta);

        C3D_Mtx& getViewMatrix();

    private:
        /* data */
        float m_posX, m_posY, m_posZ, m_rotationX, m_rotationY, m_rotationZ;
        C3D_Mtx m_view;
    };
} /* m3d */

#endif /* end of include guard: CAMERA_H */
