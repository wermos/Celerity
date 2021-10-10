#include "color.hpp"

std::ostream& operator<<(std::ostream& out, color pixelColor) {
    // Write the translated [0,255] value of each color component.
    out << pixelColor.r() << " "
        << pixelColor.g() << " "
        << pixelColor.b() << "\n";
}

color operator+(const color& c1, const color& c2) {
	return color(c1.m_color[0] + c2.m_color[0], c1.m_color[1] + c2.m_color[1],
				 c1.m_color[2] + c2.m_color[2]);
}

color operator*(double t, const color& c) {
	return color(t * c.m_color[0], t * c.m_color[1], t * c.m_color[2]);
}
