/**
 * @file sprite.hpp
 * @brief Defines the sprite class which can be used for drawing textures
 */
#pragma once
#include "graphics/drawable.hpp"
#include "graphics/vertex.hpp"
#include "graphics/boundingBox.hpp"
#include "graphics/texture.hpp"

namespace m3d {
    class Sprite: public Drawable {
    public:
        /**
         * @brief Initializes the sprite
         */
        Sprite();

        /**
         * @brief Destroys the object
         */
        virtual ~Sprite();

        /**
         * @brief Sets the x position of the sprite
         * @param t_x The x position
         */
        void setXPosition(int t_x);

        /**
         * @brief Returns the x position of the sprite
         * @return The x position
         */
        int getXPosition();

        /**
         * @brief Sets the y position of the sprite
         * @param t_y The y position
         */
        void setYPosition(int t_y);

        /**
         * @brief Returns the y position of the sprite
         * @return The y position
         */
        int getYPosition();

        /**
         * @brief Sets the position of the sprite
         * @param t_x The x position
         * @param t_y The y position
         */
        void setPosition(int t_x, int t_y);

        /**
         * @brief Sets the position of the sprite
         * @param t_vector The vector representing the position
         * @note The first component of the vector is the x position, the seconf component is the y position
         */
        void setPosition(Vector2f t_vector);

        /**
         * @brief Moves the sprite a certain offset on the x-axis
         * @param t_offset The offset to move
         */
        void moveX(int t_offset);

        /**
         * @brief Moves the sprite a certain offset on the y-axis
         * @param t_offset The offset to move
         */
        void moveY(int t_offset);

        /**
         * @brief Moves the sprite a certain offset
         * @param t_offsetX The offset to move on the x-axis
         * @param t_offsetY The offset to move on the y-axis
         */
        void move(int t_offsetX, int t_offsetY);

        /**
         * @brief Moves the sprite a certain offset
         * @param t_vector The vector to move
         * @note The first component of the vector is the offset to move on the x-axis, the second component is the offset on the y-axis
         */
        void move(Vector2f t_vector);

        /**
         * @brief Sets the width of the sprite
         * @param t_width The width
         */
        void setWidth(int t_width);

        /**
         * @brief Returns the width of the sprite
         * @return The width
         */
        int getWidth();

        /**
         * @brief Sets the height of the sprite
         * @param t_height The height
         */
        void setHeight(int t_height);

        /**
         * @brief Returns the height of the sprite
         * @return The height
         */
        int getHeight();

        /**
         * @brief Sets the dimensions if the sprite
         * @param t_width  The width
         * @param t_height The height
         */
        void setDimensions(int t_width, int t_height);

        /**
         * @brief Returns the current bounding box of the sprite
         * @return The bounding box
         */
        BoundingBox getBoundingBox();

        /**
         * @brief Sets the texture of the sprite
         * @param t_texture    The texture
         * @param t_autoresize Whether the sprite should automatically resize it's dimensions to match the dimensions of the texture
         */
        void setTexture(Texture t_texture, bool t_autoresize = true);

        /**
         * @brief Returns a reference to the Texture of the sprite
         * @return The texture
         */
        Texture& getTexture();

        /**
         * @brief Sets whether or not to stretch the texture to fit the sprite dimensions
         * @param t_stretch Whether or not to stretch the texture
         */
        void setTextureStretching(bool t_stretch);

        /**
         * @brief Returns whether or not the texture will get stretched to fit the sprite dimensions
         * @return Whether or not the texture will get stretched
         */
        bool getTextureStretching();

        /**
         * @brief Draws the shape
         * @param t_side The current 3D side (0 = left, 1 = right)
         * @param t_projection The projection uniform of the shader
         * @param t_transform The transform uniform of the shader
         * @param t_useTransform The useTransform uniform of the shader
         */
        void draw(int t_side, int t_projection, int t_transform, int t_useTransform);

    private:
        /* data */
        int m_posX, m_posY, m_width, m_height;
        Texture m_texture;
        bool m_changed, m_stretch;
        m3d::InternalTexturedVertex* m_internalVertices;
        s16* m_elementData;
    };
} /* m3d */
