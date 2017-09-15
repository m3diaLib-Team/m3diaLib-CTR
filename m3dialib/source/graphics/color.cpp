#include "graphics/color.hpp"

namespace m3d {
	Color::Color() :
	 			m_red(0),
				m_green(0),
				m_blue(0),
				m_alpha(255) { /* do nothing */ }

	Color::Color(m3d::colors::Color t_color) :
	 			m_red(RGBA8_GET_R(t_color)),
				m_green(RGBA8_GET_G(t_color)),
				m_blue(RGBA8_GET_B(t_color)),
				m_alpha(RGBA8_GET_A(t_color)) { /* do nothing */ }

	Color::Color(uint8_t t_r, uint8_t t_g, uint8_t t_b) :
	 			m_red(t_r),
				m_green(t_g),
				m_blue(t_b),
				m_alpha(255) { /* do nothing */ }

	Color::Color(uint8_t t_r, uint8_t t_g, uint8_t t_b, uint8_t t_a) :
	 			m_red(t_r),
				m_green(t_g),
				m_blue(t_b),
				m_alpha(t_a) { /* do nothing */ }

	void Color::setColor(uint8_t t_r, uint8_t t_g, uint8_t t_b) {
		m_red = t_r;
		m_green = t_g;
		m_blue = t_b;
	}

	void Color::setColor(uint8_t t_r, uint8_t t_g, uint8_t t_b, uint8_t t_a) {
		m_red = t_r;
		m_green = t_g;
		m_blue = t_b;
		m_alpha = t_a;
	}

	void Color::setRed(uint8_t t_r) {
		m_red = t_r;
	}

	uint8_t Color::getRed() {
		return m_red;
	}

	void Color::setGreen(uint8_t t_g) {
		m_green = t_g;
	}

	uint8_t Color::getGreen() {
		return m_green;
	}

	void Color::setBlue(uint8_t t_b) {
		m_blue = t_b;
	}

	uint8_t Color::getBlue() {
		return m_blue;
	}

	void Color::setAlpha(uint8_t t_a) {
		m_alpha = t_a;
	}

	uint8_t Color::getAlpha() {
		return m_alpha;
	}

	u32 Color::getRgba8() {
		return RGBA8(m_red, m_green, m_blue, m_alpha);
	}
} /* m3d */
