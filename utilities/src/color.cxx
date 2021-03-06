#include <cmath>
#include "color.hpp"

std::ostream& operator<<(std::ostream& out, const color& pixelColor) {
    // Write the translated [0,255] value of each color component.
    out << pixelColor.r() << " "
        << pixelColor.g() << " "
        << pixelColor.b();
	return out;
}

color color::combine(int samplesPerPixel) {
			// Divide the color by the number of samples.
			auto scale = 1.0 / samplesPerPixel;

			// Divide the color by the number of samples and gamma-correct for gamma=2.0.
			m_color[0] = sqrt(scale * m_color[0]);
			m_color[1] = sqrt(scale * m_color[1]);
			m_color[2] = sqrt(scale * m_color[2]);


			// Write the translated [0,255] value of each color component.
			return {clamp(m_color[0], 0.0, 0.999),
					clamp(m_color[1], 0.0, 0.999),
					clamp(m_color[2], 0.0, 0.999)};
}
