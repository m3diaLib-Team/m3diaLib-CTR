#include <citro2d.h>
#include "m3d/graphics/screen.hpp"
#include "m3d/graphics/color.hpp"
#include "m3d/private/graphics.hpp"
#include "render3d_shbin.h"

namespace m3d {
    Screen::Screen(bool t_enable3d) :
            m_clearColorTop(m3d::colors::Black),
            m_clearColorBottom(m3d::colors::Black) {
        gfxInitDefault();
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        gfxSet3D(t_enable3d);
        C3D_DepthTest(true, GPU_ALWAYS, GPU_WRITE_ALL);
        m_3dEnabled = t_enable3d;
        m_targetTopLeft  = new m3d::RenderTarget(400, 240, GFX_TOP, GFX_LEFT);
        m_targetTopRight = new m3d::RenderTarget(400, 240, GFX_TOP, GFX_RIGHT);
        m_targetBottom   = new m3d::RenderTarget(320, 240, GFX_BOTTOM, GFX_LEFT);

        u32 flags = GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO);

        C3D_RenderTargetSetOutput(m_targetTopLeft->getRenderTarget(),  GFX_TOP,    GFX_LEFT,  flags);
        C3D_RenderTargetSetOutput(m_targetTopRight->getRenderTarget(), GFX_TOP,    GFX_RIGHT, flags);
        C3D_RenderTargetSetOutput(m_targetBottom->getRenderTarget(),   GFX_BOTTOM, GFX_LEFT,  flags);

        m_dvlb = DVLB_ParseFile((u32*) render3d_shbin, render3d_shbin_size);
        shaderProgramInit(&m_shader);
        shaderProgramSetVsh(&m_shader, &m_dvlb->DVLE[0]);

        // get location of uniforms used in the vertex shader.
        m_projectionUniform = shaderInstanceGetUniformLocation(m_shader.vertexShader, "projection");
        m_modelViewUniform = shaderInstanceGetUniformLocation(m_shader.vertexShader, "modelView");
        m_lightVecUniform     = shaderInstanceGetUniformLocation(m_shader.vertexShader, "lightVec");
        m_lightHalfVecUniform = shaderInstanceGetUniformLocation(m_shader.vertexShader, "lightHalfVec");
        m_lightColorUniform     = shaderInstanceGetUniformLocation(m_shader.vertexShader, "lightClr");
        m_materialUniform     = shaderInstanceGetUniformLocation(m_shader.vertexShader, "material");

        clear();
    }

    Screen::~Screen() {
        shaderProgramFree(&m_shader);
        DVLB_Free(m_dvlb);
        C2D_Fini();
        C3D_Fini();
        gfxExit();
    }

    void Screen::set3d(bool t_enabled) {
        gfxSet3D(t_enabled);
        m_3dEnabled = t_enabled;
    }

    void Screen::setClearColor(m3d::Color t_color) {
        m_clearColorTop = t_color;
        m_clearColorBottom = t_color;
    }

    void Screen::setClearColor(m3d::Color t_color, m3d::RenderContext::ScreenTarget t_target) {
        t_target == m3d::RenderContext::ScreenTarget::Top ?
                    m_clearColorTop = t_color :
                    m_clearColorBottom = t_color;
    }

    m3d::Color Screen::getClearColor(m3d::RenderContext::ScreenTarget t_target) {
        return t_target == m3d::RenderContext::ScreenTarget::Top ? m_clearColorTop : m_clearColorBottom;
    }

    void Screen::drawTop(m3d::Drawable& t_object, m3d::RenderContext::Mode t_mode, int t_layer) {
        if (t_mode == m3d::RenderContext::Mode::Flat) {
            if(m_drawStackTop2d.count(t_layer) > 0) {
                m_drawStackTop2d[t_layer].insert(m_drawStackTop2d[t_layer].end(), &t_object);
            } else {
                std::vector<m3d::Drawable*> newStack;
                newStack.push_back(&t_object);
                m_drawStackTop2d.insert(std::make_pair(t_layer, newStack));
            }
        } else {
            if(m_drawStackTop3d.count(t_layer) > 0) {
                m_drawStackTop3d[t_layer].insert(m_drawStackTop3d[t_layer].end(), &t_object);
            } else {
                std::vector<m3d::Drawable*> newStack;
                newStack.push_back(&t_object);
                m_drawStackTop3d.insert(std::make_pair(t_layer, newStack));
            }
        }
    }

    void Screen::drawBottom(m3d::Drawable& t_object, m3d::RenderContext::Mode t_mode, int t_layer) {
        if (t_mode == m3d::RenderContext::Mode::Flat) {
            if(m_drawStackBottom2d.count(t_layer) > 0) {
                m_drawStackBottom2d[t_layer].insert(m_drawStackBottom2d[t_layer].end(), &t_object);
            } else {
                std::vector<m3d::Drawable*> newStack;
                newStack.push_back(&t_object);
                m_drawStackBottom2d.insert(std::make_pair(t_layer, newStack));
            }
        } else {
            if(m_drawStackBottom3d.count(t_layer) > 0) {
                m_drawStackBottom3d[t_layer].insert(m_drawStackBottom3d [t_layer].end(), &t_object);
            } else {
                std::vector<m3d::Drawable*> newStack;
                newStack.push_back(&t_object);
                m_drawStackBottom3d.insert(std::make_pair(t_layer, newStack));
            }
        }
    }

    void Screen::render(bool t_clear) {
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        if (t_clear) {
            m_targetTopLeft->clear();
            m_targetTopRight->clear();
            m_targetBottom->clear();
            clear();
        }

        // draw 3d
        if(m_drawStackTop3d.size() > 0 || m_drawStackBottom3d.size() > 0) {
            prepare();

            if(m_drawStackBottom3d.size() > 0) {
                C3D_FrameDrawOn(m_targetBottom->getRenderTarget());

                for(const auto &entry : m_drawStackBottom3d) { // for every layer
                    for(const auto &drawable : entry.second) { // draw every object
                        drawable->draw(m3d::RenderContext(
                                m_projectionUniform,   // projectionUniform
                                m_modelViewUniform,    // modelViewUniform
                                m_lightVecUniform,     // lightVecUniform
                                m_lightHalfVecUniform, // lightHalfVecUniform
                                m_lightColorUniform,   // lightColorUniform
                                m_materialUniform,     // materialUniform
                                m_3dEnabled, // 3dEnabled
                                m3d::RenderContext::Mode::Spatial,        // mode
                                m3d::RenderContext::Stereo3dSide::Left,   // side
                                m3d::RenderContext::ScreenTarget::Bottom, // target
                                m_projection, // projection
                                m_modelView   // model
                            ));
                    }
                }

                m_drawStackBottom3d.clear();
            }

            if (m_drawStackTop3d.size() > 0) {
                C3D_FrameDrawOn(m_targetTopLeft->getRenderTarget());

                for (const auto &entry : m_drawStackTop3d) { // for every layer
                    for (const auto &drawable : entry.second) { // draw every object
                        drawable->draw(m3d::RenderContext(
                                m_projectionUniform,   // projectionUniform
                                m_modelViewUniform,    // modelViewUniform
                                m_lightVecUniform,     // lightVecUniform
                                m_lightHalfVecUniform, // lightHalfVecUniform
                                m_lightColorUniform,   // lightColorUniform
                                m_materialUniform,     // materialUniform
                                m_3dEnabled, // 3dEnabled
                                m3d::RenderContext::Mode::Spatial,      // mode
                                m3d::RenderContext::Stereo3dSide::Left, // side
                                m3d::RenderContext::ScreenTarget::Top,  // target
                                m_projection, // projection
                                m_modelView   // model
                            ));
                    }
                }

                if (m_3dEnabled) {
                    C3D_FrameDrawOn(m_targetTopRight->getRenderTarget());

                    for (const auto &entry : m_drawStackTop3d) { // for every layer
                        for (const auto &drawable : entry.second) { // draw every object
                            drawable->draw(m3d::RenderContext(
                                    m_projectionUniform,   // projectionUniform
                                    m_modelViewUniform,    // modelViewUniform
                                    m_lightVecUniform,     // lightVecUniform
                                    m_lightHalfVecUniform, // lightHalfVecUniform
                                    m_lightColorUniform,   // lightColorUniform
                                    m_materialUniform,     // materialUniform
                                    m_3dEnabled, // 3dEnabled
                                    m3d::RenderContext::Mode::Spatial,       // mode
                                    m3d::RenderContext::Stereo3dSide::Right, // side
                                    m3d::RenderContext::ScreenTarget::Top,   // target
                                    m_projection, // projection
                                    m_modelView   // modelview
                                ));
                        }
                    }
                }

                m_drawStackTop3d.clear();
            }
        }

        // draw 2d
        if (m_drawStackTop2d.size() > 0 || m_drawStackBottom2d.size() > 0) {
            C2D_Prepare();

            if(m_drawStackBottom2d.size() > 0) {
                C2D_SceneBegin(m_targetBottom->getRenderTarget());

                for(const auto &entry : m_drawStackBottom2d) { // for every layer
                    for(const auto &drawable : entry.second) { // draw every object
                        drawable->draw(m3d::RenderContext(
                                m_projectionUniform,   // projectionUniform
                                m_modelViewUniform,    // modelViewUniform
                                m_lightVecUniform,     // lightVecUniform
                                m_lightHalfVecUniform, // lightHalfVecUniform
                                m_lightColorUniform,   // lightColorUniform
                                m_materialUniform,     // materialUniform
                                m_3dEnabled, // 3dEnabled
                                m3d::RenderContext::Mode::Flat,           // mode
                                m3d::RenderContext::Stereo3dSide::Left,   // side
                                m3d::RenderContext::ScreenTarget::Bottom, // target
                                m_projection, // projection
                                m_modelView   // modelview
                            ));
                    }
                }

                m_drawStackBottom2d.clear();
            }

            if(m_drawStackTop2d.size() > 0) {
                C2D_SceneBegin(m_targetTopLeft->getRenderTarget());

                for(const auto &entry : m_drawStackTop2d) { // for every layer
                    for(const auto &drawable : entry.second) { // draw every object
                        drawable->draw(m3d::RenderContext(
                                m_projectionUniform,   // projectionUniform
                                m_modelViewUniform,    // modelViewUniform
                                m_lightVecUniform,     // lightVecUniform
                                m_lightHalfVecUniform, // lightHalfVecUniform
                                m_lightColorUniform,   // lightColorUniform
                                m_materialUniform,     // materialUniform
                                m_3dEnabled, // 3dEnabled
                                m3d::RenderContext::Mode::Flat,         // mode
                                m3d::RenderContext::Stereo3dSide::Left, // side
                                m3d::RenderContext::ScreenTarget::Top,  // target
                                m_projection, // projection
                                m_modelView   // model
                            ));
                    }
                }

                if(m_3dEnabled) {
                    C2D_SceneBegin(m_targetTopRight->getRenderTarget());

                    for(const auto &entry : m_drawStackTop2d) { // for every layer
                        for(const auto &drawable : entry.second) { // draw every object
                            drawable->draw(m3d::RenderContext(
                                    m_projectionUniform,   // projectionUniform
                                    m_modelViewUniform,    // modelViewUniform
                                    m_lightVecUniform,     // lightVecUniform
                                    m_lightHalfVecUniform, // lightHalfVecUniform
                                    m_lightColorUniform,   // lightColorUniform
                                    m_materialUniform,     // materialUniform
                                    m_3dEnabled, // 3dEnabled
                                    m3d::RenderContext::Mode::Flat,          // mode
                                    m3d::RenderContext::Stereo3dSide::Right, // side
                                    m3d::RenderContext::ScreenTarget::Top,   // target
                                    m_projection, // projection
                                    m_modelView   // model
                                ));
                        }
                    }
                }

                m_drawStackTop2d.clear();
            }
        }

        C3D_FrameEnd(0);
    }

    int Screen::getScreenWidth(m3d::RenderContext::ScreenTarget t_target) {
        return t_target == m3d::RenderContext::ScreenTarget::Top ? 400 : 320;
    }

    int Screen::getScreenHeight() {
        return 240;
    }

    void Screen::clear() {
        C2D_TargetClear(m_targetTopLeft->getRenderTarget(), m_clearColorTop.getRgba8());
        C2D_TargetClear(m_targetTopRight->getRenderTarget(), m_clearColorTop.getRgba8());
        C2D_TargetClear(m_targetBottom->getRenderTarget(), m_clearColorBottom.getRgba8());
    }

    // private methods
    void Screen::prepare() {
        C3D_BindProgram(&m_shader);

        // initialize and configure attributes
        m_attributeInfo = C3D_GetAttrInfo();
        AttrInfo_Init(m_attributeInfo);
        AttrInfo_AddLoader(m_attributeInfo, 0, GPU_FLOAT, 3); // v0=position
        AttrInfo_AddLoader(m_attributeInfo, 1, GPU_FLOAT, 2); // v1=texcoord
        AttrInfo_AddLoader(m_attributeInfo, 2, GPU_FLOAT, 3); // v2=normal

        // Configure the first fragment shading substage to blend the fragment primary color
        // with the fragment secondary color.
        // See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
        // C3D_TexEnv* environment = C3D_GetTexEnv(0);
        // C3D_TexEnvSrc(environment, C3D_Both, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR, (GPU_TEVSRC) 0);
        // C3D_TexEnvOp(environment, C3D_Both, 0, 0, 0);
        // C3D_TexEnvFunc(environment, C3D_Both, GPU_ADD);
        C3D_TexEnv* env = C3D_GetTexEnv(0);
        C3D_TexEnvInit(env);
        C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR);
        C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);
    }
} /* m3d */
