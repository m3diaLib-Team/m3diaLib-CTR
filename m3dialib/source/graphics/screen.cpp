#include <citro2d.h>
#include "m3d/core/applet.hpp"
#include "m3d/graphics/screen.hpp"
#include "m3d/graphics/color.hpp"
#include "m3d/private/graphics.hpp"
#include "render3d_shbin.h"

namespace m3d {
    Screen::Screen(bool t_enable3d) :
            m_3dEnabled(t_enable3d),
            m_useCulling(true),
            m_clearColorTop(m3d::Color(0, 0, 0)),
            m_clearColorBottom(m3d::Color(0, 0, 0)),
            m_cameraTop(m3d::priv::graphics::defaultCamera0),
            m_cameraBottom(m3d::priv::graphics::defaultCamera1),
            m_useFogTop(false),
            m_useFogBottom(false),
            m_fogDensityTop(0.05),
            m_fogDensityBottom(0.05) {
        gfxInitDefault();
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        gfxSet3D(m_3dEnabled);
        m_targetTopLeft  = new m3d::RenderTarget(400, 240);
        m_targetTopRight = new m3d::RenderTarget(400, 240);
        m_targetBottom   = new m3d::RenderTarget(320, 240);

        u32 flags = GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO);

        C3D_RenderTargetSetOutput(m_targetTopLeft->getRenderTarget(),  GFX_TOP,    GFX_LEFT,  flags);
        C3D_RenderTargetSetOutput(m_targetTopRight->getRenderTarget(), GFX_TOP,    GFX_RIGHT, flags);
        C3D_RenderTargetSetOutput(m_targetBottom->getRenderTarget(),   GFX_BOTTOM, GFX_LEFT,  flags);

        m_dvlb = DVLB_ParseFile((u32*) render3d_shbin, render3d_shbin_size);
        shaderProgramInit(&m_shader);
        shaderProgramSetVsh(&m_shader, &m_dvlb->DVLE[0]);

        // get location of uniforms used in the vertex shader.
        m_projectionUniform = shaderInstanceGetUniformLocation(m_shader.vertexShader, "projection");
        m_modelUniform = shaderInstanceGetUniformLocation(m_shader.vertexShader, "model");
        m_viewUniform = shaderInstanceGetUniformLocation(m_shader.vertexShader, "view");

        AttrInfo_Init(&m_attributeInfo);
        AttrInfo_AddLoader(&m_attributeInfo, 0, GPU_FLOAT, 3); // v0=position
        AttrInfo_AddLoader(&m_attributeInfo, 1, GPU_FLOAT, 2); // v1=texcoord
        AttrInfo_AddLoader(&m_attributeInfo, 2, GPU_FLOAT, 3); // v2=normal

        // light
        C3D_FVec lightVec;

        C3D_LightEnvInit(&m_lightEnvTop);
        LightLut_Phong(&m_lutPhongTop, 30);
        C3D_LightEnvLut(&m_lightEnvTop, GPU_LUT_D0, GPU_LUTINPUT_LN, false, &m_lutPhongTop);
        lightVec = FVec4_New(0.0f, 0.0f, -0.5f, 1.0f);
        C3D_LightInit(&m_lightTop, &m_lightEnvTop);
        C3D_LightColor(&m_lightTop, 1.0, 1.0, 1.0);
        C3D_LightPosition(&m_lightTop, &lightVec);

        C3D_LightEnvInit(&m_lightEnvBottom);
        LightLut_Phong(&m_lutPhongBottom, 30);
        C3D_LightEnvLut(&m_lightEnvBottom, GPU_LUT_D0, GPU_LUTINPUT_LN, false, &m_lutPhongBottom);
        lightVec = FVec4_New(0.0f, 0.0f, -0.5f, 1.0f);
        C3D_LightInit(&m_lightBottom, &m_lightEnvBottom);
        C3D_LightColor(&m_lightBottom, 1.0, 1.0, 1.0);
        C3D_LightPosition(&m_lightBottom, &lightVec);

        clear();
    }

    Screen::~Screen() {
        C2D_Fini();
        C3D_Fini();
        gfxExit();
        shaderProgramFree(&m_shader);
        DVLB_Free(m_dvlb);
        delete m_targetTopLeft;
        delete m_targetTopRight;
        delete m_targetBottom;
    }

    void Screen::set3d(bool t_enabled) {
        gfxSet3D(t_enabled);
        m_3dEnabled = t_enabled;
    }

    void Screen::useCulling(bool t_useCulling) {
        m_useCulling = t_useCulling;
    }

    bool Screen::isUsingCulling() {
        return m_useCulling;
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
                m_drawStackTop2d[t_layer].insert(m_drawStackTop2d[t_layer].end(), std::make_pair(&t_object, [](){return true;}));
            } else {
                std::vector<std::pair<m3d::Drawable*, std::function<bool()>>> newStack;
                newStack.push_back(std::make_pair(&t_object, [](){return true;}));
                m_drawStackTop2d.insert(std::make_pair(t_layer, newStack));
            }
        } else {
            if(m_drawStackTop3d.count(t_layer) > 0) {
                m_drawStackTop3d[t_layer].insert(m_drawStackTop3d[t_layer].end(), std::make_pair(&t_object, [](){return true;}));
            } else {
                std::vector<std::pair<m3d::Drawable*, std::function<bool()>>> newStack;
                newStack.push_back(std::make_pair(&t_object, [](){return true;}));
                m_drawStackTop3d.insert(std::make_pair(t_layer, newStack));
            }
        }
    }

    void Screen::drawTop(m3d::Drawable& t_object, std::function<bool()> t_shadingFunction, m3d::RenderContext::Mode t_mode, int t_layer) {
        if (t_mode == m3d::RenderContext::Mode::Flat) {
            if(m_drawStackTop2d.count(t_layer) > 0) {
                m_drawStackTop2d[t_layer].insert(m_drawStackTop2d[t_layer].end(), std::make_pair(&t_object, t_shadingFunction));
            } else {
                std::vector<std::pair<m3d::Drawable*, std::function<bool()>>> newStack;
                newStack.push_back(std::make_pair(&t_object, t_shadingFunction));
                m_drawStackTop2d.insert(std::make_pair(t_layer, newStack));
            }
        } else {
            if(m_drawStackTop3d.count(t_layer) > 0) {
                m_drawStackTop3d[t_layer].insert(m_drawStackTop3d[t_layer].end(), std::make_pair(&t_object, t_shadingFunction));
            } else {
                std::vector<std::pair<m3d::Drawable*, std::function<bool()>>> newStack;
                newStack.push_back(std::make_pair(&t_object, t_shadingFunction));
                m_drawStackTop3d.insert(std::make_pair(t_layer, newStack));
            }
        }
    }

    void Screen::drawBottom(m3d::Drawable& t_object, m3d::RenderContext::Mode t_mode, int t_layer) {
        if (t_mode == m3d::RenderContext::Mode::Flat) {
            if(m_drawStackBottom2d.count(t_layer) > 0) {
                m_drawStackBottom2d[t_layer].insert(m_drawStackBottom2d[t_layer].end(), std::make_pair(&t_object, [](){return true;}));
            } else {
                std::vector<std::pair<m3d::Drawable*, std::function<bool()>>> newStack;
                newStack.push_back(std::make_pair(&t_object, [](){return true;}));
                m_drawStackBottom2d.insert(std::make_pair(t_layer, newStack));
            }
        } else {
            if(m_drawStackBottom3d.count(t_layer) > 0) {
                m_drawStackBottom3d[t_layer].insert(m_drawStackBottom3d[t_layer].end(), std::make_pair(&t_object, [](){return true;}));
            } else {
                std::vector<std::pair<m3d::Drawable*, std::function<bool()>>> newStack;
                newStack.push_back(std::make_pair(&t_object, [](){return true;}));
                m_drawStackBottom3d.insert(std::make_pair(t_layer, newStack));
            }
        }
    }

    void Screen::drawBottom(m3d::Drawable& t_object, std::function<bool()> t_shadingFunction, m3d::RenderContext::Mode t_mode, int t_layer) {
        if (t_mode == m3d::RenderContext::Mode::Flat) {
            if(m_drawStackBottom2d.count(t_layer) > 0) {
                m_drawStackBottom2d[t_layer].insert(m_drawStackBottom2d[t_layer].end(), std::make_pair(&t_object, t_shadingFunction));
            } else {
                std::vector<std::pair<m3d::Drawable*, std::function<bool()>>> newStack;
                newStack.push_back(std::make_pair(&t_object, t_shadingFunction));
                m_drawStackBottom2d.insert(std::make_pair(t_layer, newStack));
            }
        } else {
            if(m_drawStackBottom3d.count(t_layer) > 0) {
                m_drawStackBottom3d[t_layer].insert(m_drawStackBottom3d[t_layer].end(), std::make_pair(&t_object, t_shadingFunction));
            } else {
                std::vector<std::pair<m3d::Drawable*, std::function<bool()>>> newStack;
                newStack.push_back(std::make_pair(&t_object, t_shadingFunction));
                m_drawStackBottom3d.insert(std::make_pair(t_layer, newStack));
            }
        }
    }

    void Screen::render(bool t_clear) {
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        if (t_clear) {
            C2D_SceneBegin(m_targetTopLeft->getRenderTarget());
            m_targetTopLeft->clear();
            C2D_SceneBegin(m_targetTopRight->getRenderTarget());
            m_targetTopRight->clear();
            C2D_SceneBegin(m_targetBottom->getRenderTarget());
            m_targetBottom->clear();
            clear();
        }

        // draw 3d
        if(m_drawStackTop3d.size() > 0 || m_drawStackBottom3d.size() > 0) {
            prepare();
            C3D_DepthTest(true, GPU_GEQUAL, GPU_WRITE_ALL);
            Mtx_PerspStereoTilt(&m_projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioBot, 0.01f, 1000.0f, 0, 2.0f, false);

            C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_projectionUniform, &m_projection);
            C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_viewUniform, &m_cameraBottom.getViewMatrix());

            if(m_drawStackBottom3d.size() > 0) {
                C3D_FrameDrawOn(m_targetBottom->getRenderTarget());
                prepareLights(m3d::RenderContext::ScreenTarget::Bottom);
                if (m_useFogBottom) prepareFog(m3d::RenderContext::ScreenTarget::Bottom);

                for(const auto &entry : m_drawStackBottom3d) { // for every layer
                    for(const auto &drawable : entry.second) { // draw every object
                        if (drawable.second()) {
                            drawable.first->draw(m3d::RenderContext(
                                m_modelUniform, // modelUniform
                                m_3dEnabled, // 3dEnabled
                                m3d::RenderContext::Mode::Spatial,        // mode
                                m3d::RenderContext::Stereo3dSide::Left,   // side
                                m3d::RenderContext::ScreenTarget::Bottom, // target
                                m_model,  // model
                                m_lightEnvBottom, // lightEnv
                                m_lightBottom,    // light
                                m_lutPhongBottom  // lutPhong
                            ));
                        }
                    }
                }

                m_drawStackBottom3d.clear();
            }

            if (m_drawStackTop3d.size() > 0) {
                C3D_FrameDrawOn(m_targetTopLeft->getRenderTarget());
                prepareLights(m3d::RenderContext::ScreenTarget::Top);
                if (m_useFogTop) prepareFog(m3d::RenderContext::ScreenTarget::Top);

                // tilt stereo perspective
                if (m_3dEnabled) {
                    Mtx_PerspStereoTilt(&m_projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, -(m3d::Applet::get3dSliderState() / 3.0f), 2.0f, false);
                } else {
                    Mtx_PerspStereoTilt(&m_projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, 0, 2.0f, false);
                }

                C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_projectionUniform, &m_projection);
                C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_viewUniform, &m_cameraTop.getViewMatrix());

                for (const auto &entry : m_drawStackTop3d) { // for every layer
                    for (const auto &drawable : entry.second) { // draw every object
                        if (drawable.second()) {
                            drawable.first->draw(m3d::RenderContext(
                                m_modelUniform, // modelUniform
                                m_3dEnabled, // 3dEnabled
                                m3d::RenderContext::Mode::Spatial,      // mode
                                m3d::RenderContext::Stereo3dSide::Left, // side
                                m3d::RenderContext::ScreenTarget::Top,  // target
                                m_model,  // model
                                m_lightEnvTop, // lightEnv
                                m_lightTop,    // light
                                m_lutPhongTop  // lutPhong
                            ));
                        }
                    }
                }

                if (m_3dEnabled && m3d::Applet::get3dSliderState() > 0.0f) {
                    C3D_FrameDrawOn(m_targetTopRight->getRenderTarget());

                    // tilt stereo perspective
                    if (m_3dEnabled) {
                        Mtx_PerspStereoTilt(&m_projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, m3d::Applet::get3dSliderState() / 3.0f, 2.0f, false);
                    } else {
                        Mtx_PerspStereoTilt(&m_projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, 0, 2.0f, false);
                    }

                    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_projectionUniform, &m_projection);

                    for (const auto &entry : m_drawStackTop3d) { // for every layer
                        for (const auto &drawable : entry.second) { // draw every object
                            if (drawable.second()) {
                                drawable.first->draw(m3d::RenderContext(
                                    m_modelUniform, // modelUniform
                                    m_3dEnabled, // 3dEnabled
                                    m3d::RenderContext::Mode::Spatial,       // mode
                                    m3d::RenderContext::Stereo3dSide::Right, // side
                                    m3d::RenderContext::ScreenTarget::Top,   // target
                                    m_model,  // model
                                    m_lightEnvTop, // lightEnv
                                    m_lightTop,    // light
                                    m_lutPhongTop  // lutPhong
                                ));
                            }
                        }
                    }
                }

                m_drawStackTop3d.clear();
            }
        }

        // draw 2d
        if (m_drawStackTop2d.size() > 0 || m_drawStackBottom2d.size() > 0) {
            C2D_Prepare();
            C3D_DepthTest(true, GPU_ALWAYS, GPU_WRITE_ALL);

            if(m_drawStackBottom2d.size() > 0) {
                C2D_SceneBegin(m_targetBottom->getRenderTarget());

                for(const auto &entry : m_drawStackBottom2d) { // for every layer
                    for(const auto &drawable : entry.second) { // draw every object
                        if (drawable.second()) {
                            drawable.first->draw(m3d::RenderContext(
                                m_modelUniform, // modelUniform
                                m_3dEnabled, // 3dEnabled
                                m3d::RenderContext::Mode::Flat,           // mode
                                m3d::RenderContext::Stereo3dSide::Left,   // side
                                m3d::RenderContext::ScreenTarget::Bottom, // target
                                m_model,  // model
                                m_lightEnvBottom, // lightEnv
                                m_lightBottom,    // light
                                m_lutPhongBottom  // lutPhong
                            ));
                        }
                    }
                }

                m_drawStackBottom2d.clear();
            }

            if(m_drawStackTop2d.size() > 0) {
                C2D_SceneBegin(m_targetTopLeft->getRenderTarget());

                for(const auto &entry : m_drawStackTop2d) { // for every layer
                    for(const auto &drawable : entry.second) { // draw every object
                        if (drawable.second()) {
                            drawable.first->draw(m3d::RenderContext(
                                m_modelUniform, // modelUniform
                                m_3dEnabled, // 3dEnabled
                                m3d::RenderContext::Mode::Flat,         // mode
                                m3d::RenderContext::Stereo3dSide::Left, // side
                                m3d::RenderContext::ScreenTarget::Top,  // target
                                m_model,  // model
                                m_lightEnvTop, // lightEnv
                                m_lightTop,    // light
                                m_lutPhongTop  // lutPhong
                            ));
                        }
                    }
                }

                if(m_3dEnabled && m3d::Applet::get3dSliderState() > 0.0f) {
                    C2D_SceneBegin(m_targetTopRight->getRenderTarget());

                    for(const auto &entry : m_drawStackTop2d) { // for every layer
                        for(const auto &drawable : entry.second) { // draw every object
                            if (drawable.second()) {
                                drawable.first->draw(m3d::RenderContext(
                                    m_modelUniform, // modelUniform
                                    m_3dEnabled, // 3dEnabled
                                    m3d::RenderContext::Mode::Flat,          // mode
                                    m3d::RenderContext::Stereo3dSide::Right, // side
                                    m3d::RenderContext::ScreenTarget::Top,   // target
                                    m_model,  // model
                                    m_lightEnvTop, // lightEnv
                                    m_lightTop,    // light
                                    m_lutPhongTop  // lutPhong
                                ));
                            }
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

    void Screen::setCamera(m3d::Camera t_camera, m3d::RenderContext::ScreenTarget t_target) {
        switch (t_target) {
            case m3d::RenderContext::ScreenTarget::Top:
                m_cameraTop = t_camera;
                break;
            default:
                m_cameraBottom = t_camera;
        }
    }

    m3d::Camera& Screen::getCamera(m3d::RenderContext::ScreenTarget t_target) {
        return (t_target == m3d::RenderContext::ScreenTarget::Top ? m_cameraTop : m_cameraBottom);
    }

    void Screen::useFog(bool t_useFog, m3d::RenderContext::ScreenTarget t_target) {
        if (t_target == m3d::RenderContext::ScreenTarget::Top) {
            m_useFogTop = t_useFog;
        } else {
            m_useFogBottom = t_useFog;
        }
    }

    bool Screen::getUseFog(m3d::RenderContext::ScreenTarget t_target) {
        return (t_target == m3d::RenderContext::ScreenTarget::Top ? m_useFogTop : m_useFogBottom);
    }

    void Screen::setFogDensity(float t_density, m3d::RenderContext::ScreenTarget t_target) {
        if (t_target == m3d::RenderContext::ScreenTarget::Top) {
            m_fogDensityTop = t_density;
        } else {
            m_fogDensityBottom = t_density;
        }
    }

    float Screen::getFogDensity(m3d::RenderContext::ScreenTarget t_target) {
        return (t_target == m3d::RenderContext::ScreenTarget::Top ? m_fogDensityTop : m_fogDensityBottom);
    }

    // private methods
    void Screen::prepare() {
        C3D_BindProgram(&m_shader);

        // initialize and configure attributes
        C3D_SetAttrInfo(&m_attributeInfo);

        // Configure the first fragment shading substage to blend the fragment primary color
        // with the fragment secondary color.
        // See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
        C3D_TexEnv* env = C3D_GetTexEnv(0);
        C3D_TexEnvInit(env);
        C3D_TexEnvSrc(env, C3D_Both, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR, GPU_PRIMARY_COLOR);
        C3D_TexEnvFunc(env, C3D_Both, GPU_ADD);

        C3D_TexEnvInit(C3D_GetTexEnv(1));
        C3D_TexEnvInit(C3D_GetTexEnv(2));
        C3D_TexEnvInit(C3D_GetTexEnv(3));
        C3D_TexEnvInit(C3D_GetTexEnv(4));
        C3D_TexEnvInit(C3D_GetTexEnv(5));

        C3D_CullFace(m_useCulling ? GPU_CULL_BACK_CCW : GPU_CULL_NONE);
    }

    void Screen::prepareFog(m3d::RenderContext::ScreenTarget t_target) {
        switch (t_target) {
            case m3d::RenderContext::ScreenTarget::Bottom:
                FogLut_Exp(&m_fogLutBottom, m_fogDensityBottom, 1.5f, 0.01f, 20.0f);
                C3D_FogGasMode(GPU_FOG, GPU_PLAIN_DENSITY, false);
                C3D_FogColor(m_clearColorTop.getRgb8());
                C3D_FogLutBind(&m_fogLutBottom);
                break;
            default:
                FogLut_Exp(&m_fogLutTop, m_fogDensityTop, 1.5f, 0.01f, 20.0f);
                C3D_FogGasMode(GPU_FOG, GPU_PLAIN_DENSITY, false);
                C3D_FogColor(m_clearColorTop.getRgb8());
                C3D_FogLutBind(&m_fogLutTop);
        }
    }

    void Screen::prepareLights(m3d::RenderContext::ScreenTarget t_target) {
        switch (t_target) {
            case m3d::RenderContext::ScreenTarget::Bottom:
                C3D_LightEnvBind(&m_lightEnvBottom);
                break;
            default:
                C3D_LightEnvBind(&m_lightEnvTop);
        }
    }
} /* m3d */
