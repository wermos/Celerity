#include "color.hpp"

std::ostream& operator<<(std::ostream& out, color pixelColor) {
    // Write the translated [0,255] value of each color component.
    out << pixelColor.r() << " "
        << pixelColor.g() << " "
        << pixelColor.b() << "\n";
}
