#include <citro2d.h>
#include "graphics/screen.hpp"
#include "graphics/color.hpp"

namespace m3d {
    Screen::Screen(bool t_enable3d) :
            m_clearColorTop(m3d::colors::BLACK),
            m_clearColorBottom(m3d::colors::BLACK) {
        gfxInitDefault();
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        C2D_Prepare();
        gfxSet3D(t_enable3d);
        C3D_DepthTest(true, GPU_ALWAYS, GPU_WRITE_ALL);
        m_3dEnabled = t_enable3d;
        m_targetTopLeft  = new m3d::RenderTarget(400, 240, GFX_TOP, GFX_LEFT);
        m_targetTopRight = new m3d::RenderTarget(400, 240, GFX_TOP, GFX_RIGHT);
        m_targetBottom   = new m3d::RenderTarget(320, 240, GFX_BOTTOM, GFX_LEFT);

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

    void Screen::setClearColor(m3d::Color t_color, m3d::ScreenTarget t_target) {
        t_target == SCREEN_TOP ?
                    m_clearColorTop = t_color :
                    m_clearColorBottom = t_color;
    }

    m3d::Color Screen::getClearColor(m3d::ScreenTarget t_target) {
        return t_target == SCREEN_TOP ? m_clearColorTop : m_clearColorBottom;
    }

    void Screen::drawTop(m3d::Drawable& t_object, int t_layer) {
        if(m_drawStackTop.count(t_layer) > 0) {
            m_drawStackTop[t_layer].insert(m_drawStackTop[t_layer].end(), &t_object);
        } else {
            std::vector<m3d::Drawable*> newStack;
            newStack.push_back(&t_object);
            m_drawStackTop.insert(std::make_pair(t_layer, newStack));
        }
    }

    void Screen::drawBottom(m3d::Drawable& t_object, int t_layer) {
        if(m_drawStackBottom.count(t_layer) > 0) {
            m_drawStackBottom[t_layer].insert(m_drawStackBottom[t_layer].end(), &t_object);
        } else {
            std::vector<m3d::Drawable*> newStack;
            newStack.push_back(&t_object);
            m_drawStackBottom.insert(std::make_pair(t_layer, newStack));
        }
    }

    void Screen::render(bool t_clear) {
        if(m_drawStackTop.size() > 0 || m_drawStackBottom.size() > 0) {
            C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

            if (t_clear) clear();

            if(m_drawStackBottom.size() > 0) {
                C2D_SceneBegin(m_targetBottom->getRenderTarget());

                for(const auto &entry : m_drawStackBottom) { // for every layer
                    for(const auto &drawable : entry.second) { // draw every object
                        drawable->draw(m3d::SIDE_LEFT);
                    }
                }
            }

            if(m_drawStackTop.size() > 0) {
                C2D_SceneBegin(m_targetTopLeft->getRenderTarget());

                for(const auto &entry : m_drawStackTop) { // for every layer
                    for(const auto &drawable : entry.second) { // draw every object
                        drawable->draw(m3d::SIDE_LEFT);
                    }
                }

                if(m_3dEnabled) {
                    C2D_SceneBegin(m_targetTopRight->getRenderTarget());

                    for(const auto &entry : m_drawStackTop) { // for every layer
                        for(const auto &drawable : entry.second) { // draw every object
                            drawable->draw(m3d::SIDE_RIGHT);
                        }
                    }
                }
            }

            C3D_FrameEnd(0);
            m_drawStackTop.clear();
            m_drawStackBottom.clear();
        }
    }

    int Screen::getScreenWidth(m3d::ScreenTarget t_target) {
        return t_target == SCREEN_TOP ? 400 : 320;
    }

    int Screen::getScreenHeight() {
        return 240;
    }

    // private methods
    void Screen::clear() {
        C2D_TargetClear(m_targetTopLeft->getRenderTarget(), m_clearColorTop.getRgba8());
        C2D_TargetClear(m_targetTopRight->getRenderTarget(), m_clearColorTop.getRgba8());
        C2D_TargetClear(m_targetBottom->getRenderTarget(), m_clearColorBottom.getRgba8());
    }
} /* m3d */
