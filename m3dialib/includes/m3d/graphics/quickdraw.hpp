/**
 * @file quickdraw.hpp
 * @brief Defines the quickdraw namespace and it's functions
 */
#ifndef QUICKDRAW_H
#define QUICKDRAW_H
#pragma once

namespace m3d {
    class RenderTarget;
    class Shader;
    class Texture;
    struct Vertex;

    /**
     * @brief The quickdraw namespace
     */
    namespace quickdraw {
        enum class StencilOp {
            Keep = 0,      ///< Keep old stencil value
            Zero,          ///< Zero (0)
            Replace,       ///< Replace old value
            Increment,     ///< Increment value (clamped between [0,255])
            Decrement,     ///< Decrement value (clamped between [0,255])
            Invert,        ///< Invert value
            IncrementWrap, ///< Increment value (wrap around)
            DecrementWrap  ///< Decrement value (wrap around)
        };

        enum class TestFunction {
            Never = 0, ///< Never pass
            Always,    ///< Always pass
            Equal,     ///< Pass if equal
            NotEqual,  ///< Pass of not equal
            Less,      ///< Pass if less than
            Lequal,    ///< Pass if less than or equal
            Greater,   ///< Pass if greater than
            Gequal     ///< Pass if greater than or equal
        };

        extern bool texturesEnabled;

        void addVertex(m3d::Vertex t_vertex);

        void prepareForTexture(bool t_textureBound = true);

        void bindTexture(m3d::Texture& t_tex, int t_texEnv = 0);

        void enableCulling(bool t_enable, bool t_front = false);

        void useRenderTarget(m3d::RenderTarget& t_target);

        void enableStencilBuffer(bool t_enable,
                                 m3d::quickdraw::TestFunction t_function,
                                 int t_ref = 1,
                                 int t_inputMask = 0xFF,
                                 int t_writeMask = 0xFF);

        void setStencilOp(m3d::quickdraw::StencilOp t_sfail = StencilOp::Keep,
                          m3d::quickdraw::StencilOp t_dfail = StencilOp::Keep,
                          m3d::quickdraw::StencilOp t_pass = StencilOp::Replace);

        void useShader(m3d::Shader& t_shader);

        void draw();
    } /* quickdraw */

    /**
     * @brief Alias for the quickdraw namespace, for convenience
     */
    namespace qdraw = quickdraw;
} /* m3d */

#endif /* end of include guard: QUICKDRAW_H */
