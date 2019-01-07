#include "m3d/graphics/quickdraw.hpp"
#include "m3d/graphics/texture.hpp"
#include "m3d/graphics/renderTarget.hpp"
#include "m3d/graphics/vertex.hpp"
#include "m3d/private/graphics.hpp"

namespace m3d {
    namespace quickdraw {
        bool texturesEnabled = false;

        void addVertex(m3d::Vertex t_vertex) {
            priv::graphics::GPU::addVertex(t_vertex);
        }

        void prepareForTexture(bool t_textureBound) {
            C3D_TexEnv* env;

            switch (t_textureBound) {
                case true:
                    if (!texturesEnabled) {
                        texturesEnabled = true;

                        // ambient/diffuse
                        env = C3D_GetTexEnv(0);
                        C3D_TexEnvInit(env);

                        C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_FRAGMENT_PRIMARY_COLOR, GPU_PRIMARY_COLOR);
                        C3D_TexEnvSrc(env, C3D_Alpha, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR);

                        C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);

                        // specular
                        env = C3D_GetTexEnv(1);
                        C3D_TexEnvInit(env);

                        C3D_TexEnvSrc(env, C3D_Both, GPU_PREVIOUS, GPU_FRAGMENT_SECONDARY_COLOR, GPU_PRIMARY_COLOR);

                        C3D_TexEnvFunc(env, C3D_RGB, GPU_ADD);
                        C3D_TexEnvFunc(env, C3D_Alpha, GPU_REPLACE);
                    }

                    break;
                default:
                    if (texturesEnabled) {
                        texturesEnabled = false;
                        env = C3D_GetTexEnv(0);
                        C3D_TexEnvInit(env);

                        C3D_TexEnvSrc(env, C3D_RGB, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR, GPU_PRIMARY_COLOR);
                        C3D_TexEnvSrc(env, C3D_Alpha, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR);

                        C3D_TexEnvFunc(env, C3D_RGB, GPU_ADD);
                        C3D_TexEnvFunc(env, C3D_Alpha, GPU_MODULATE);

                        C3D_TexEnvInit(C3D_GetTexEnv(1));
                    }
            }
        }

        void bindTexture(m3d::Texture& t_tex, int t_texEnv) {
            C3D_TexSetFilter(t_tex.getTexture(), GPU_LINEAR, GPU_LINEAR);
            C3D_TexBind(t_texEnv, t_tex.getTexture());
        }

        void enableCulling(bool t_enable, bool t_front) {
            C3D_CullFace(t_enable ? (t_front ? GPU_CULL_FRONT_CCW : GPU_CULL_BACK_CCW) : GPU_CULL_NONE);
        }

        void useRenderTarget(m3d::RenderTarget& t_target) {
            C3D_FrameDrawOn(t_target.getRenderTarget());
        }

        void enableStencilBuffer(bool t_enable,
                                 m3d::quickdraw::TestFunction t_function,
                                 int t_ref,
                                 int t_inputMask,
                                 int t_writeMask) {
            C3D_StencilTest(t_enable, (GPU_TESTFUNC) t_function, t_ref, t_inputMask, t_writeMask);
        }

        void setStencilOp(m3d::quickdraw::StencilOp t_sfail,
                          m3d::quickdraw::StencilOp t_dfail,
                          m3d::quickdraw::StencilOp t_pass) {
            C3D_StencilOp((GPU_STENCILOP) t_sfail, (GPU_STENCILOP) t_dfail, (GPU_STENCILOP) t_pass);
        }

        void useShader(m3d::Shader& t_shader) {

        }

        void draw() {
            priv::graphics::GPU::draw();
        }
    } /* quickdraw */
} /* m3d */
