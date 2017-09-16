#include "graphics/screen.hpp"
#include "graphics/color.hpp"
#include "shader_shbin.h"

/**
 * @brief Used to transfer the final rendered display to the framebuffer
 */
#define DISPLAY_TRANSFER_FLAGS \
(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

namespace m3d {
	Screen::Screen(bool t_enable3d) {
		gfxInitDefault();
		C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
		gfxSet3D(t_enable3d);
		m_3dEnabled = t_enable3d;

		u8* leftFrameBuffer = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, nullptr, nullptr);
		u8* rightFrameBuffer = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, nullptr, nullptr);
		u8* bottomFrameBuffer = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, nullptr, nullptr);
		memset(leftFrameBuffer, 0, 400 * 240 * 3);
		memset(rightFrameBuffer, 0, 400 * 240 * 3);
		memset(bottomFrameBuffer, 0, 320 * 240 * 3);

		m_targetTopLeft 	= new m3d::RenderTarget(400, 240);
		m_targetTopRight 	= new m3d::RenderTarget(400, 240);
		m_targetBottom 		= new m3d::RenderTarget(320, 240);
		C3D_RenderTargetSetOutput(m_targetTopLeft->getRenderTarget(),  GFX_TOP,    GFX_LEFT,  DISPLAY_TRANSFER_FLAGS);
		C3D_RenderTargetSetOutput(m_targetTopRight->getRenderTarget(), GFX_TOP,    GFX_RIGHT, DISPLAY_TRANSFER_FLAGS);
		C3D_RenderTargetSetOutput(m_targetBottom->getRenderTarget(), GFX_BOTTOM, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

		// Load the vertex shader, create a shader program and bind it
		m_dvlb = DVLB_ParseFile((u32*) shader_shbin, shader_shbin_size);
		shaderProgramInit(&m_shader);
		shaderProgramSetVsh(&m_shader, &m_dvlb->DVLE[0]);
		C3D_BindProgram(&m_shader);

		// Get the location of the uniforms
		m_projection = shaderInstanceGetUniformLocation(m_shader.vertexShader, "projection");
		m_transform = shaderInstanceGetUniformLocation(m_shader.vertexShader, "transform");
		m_useTransform = shaderInstanceGetUniformLocation(m_shader.vertexShader, "useTransform");
	}

	Screen::~Screen() {
		shaderProgramFree(&m_shader);
		DVLB_Free(m_dvlb);
		C3D_Fini();
		gfxExit();
	}

	void Screen::set3d(bool t_enabled) {
		gfxSet3D(t_enabled);
		m_3dEnabled = t_enabled;
	}

	void Screen::forceClear() {
			u8* leftFrameBuffer = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, nullptr, nullptr);
			u8* rightFrameBuffer = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, nullptr, nullptr);
			u8* bottomFrameBuffer = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, nullptr, nullptr);

			memset(leftFrameBuffer, 0, 400 * 240 * 3);
			memset(rightFrameBuffer, 0, 400 * 240 * 3);
			memset(bottomFrameBuffer, 0, 320 * 240 * 3);
	}

	int Screen::getProjectionUniform() {
		return m_projection;
	}

	int Screen::getTransformUniform() {
		return m_transform;
	}

	int Screen::getUseTransformUniform() {
		return m_useTransform;
	}

	void Screen::drawTop(m3d::Drawable& t_object, int t_layer) {
		if(m_drawStackTop.count(t_layer) > 0) {
			m_drawStackTop[t_layer].push_back(&t_object);
		} else {
			std::vector<m3d::Drawable*> newStack;
			newStack.push_back(&t_object);
			m_drawStackTop.insert(std::make_pair(t_layer, newStack));
		}
	}

	void Screen::drawBottom(m3d::Drawable& t_object, int t_layer) {
		if(m_drawStackBottom.count(t_layer) > 0) {
			m_drawStackBottom[t_layer].push_back(&t_object);
		} else {
			std::vector<m3d::Drawable*> newStack;
			newStack.push_back(&t_object);
			m_drawStackBottom.insert(std::make_pair(t_layer, newStack));
		}
	}

	void Screen::render() {
		if(m_drawStackTop.size() > 0 || m_drawStackBottom.size() > 0) {
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

			if(m_drawStackBottom.size() > 0) {
				C3D_FrameDrawOn(m_targetBottom->getRenderTarget());

				for(const auto &entry : m_drawStackBottom) {
					for(const auto &drawable : entry.second) {
						C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_projection, m_targetBottom->getProjectionMatrix());
						drawable->draw(m3d::SIDE_LEFT, m_projection, m_transform, m_useTransform);
					}
				}
			}

			if(m_drawStackTop.size() > 0) {
				C3D_FrameDrawOn(m_targetTopLeft->getRenderTarget());

				for(const auto &entry : m_drawStackTop) {
					for(const auto &drawable : entry.second) {
						C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_projection, m_targetTopLeft->getProjectionMatrix());
						drawable->draw(m3d::SIDE_LEFT, m_projection, m_transform, m_useTransform);
					}
				}

				if(m_3dEnabled) {
					C3D_FrameDrawOn(m_targetTopRight->getRenderTarget());

					for(const auto &entry : m_drawStackTop) {
						for(const auto &drawable : entry.second) {
							C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_projection, m_targetTopRight->getProjectionMatrix());
							drawable->draw(m3d::SIDE_RIGHT, m_projection, m_transform, m_useTransform);
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
		return (t_target == SCREEN_TOP ? 400 : 320);
	}

	int Screen::getScreenHeight() {
		return 240;
	}
} /* m3d */
