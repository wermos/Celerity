#include <iostream>

#include "vec3.hpp"
#include "color.hpp"

int main() {

    // Image
    const int imageWidth = 256;
    const int imageHeight = 256;

    // Render
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    //PPM format starts with
    //P3
    //<width> <height>
    //<max value of color>
    //where "P3" tells the viewer that the colors are in ASCII
    //<width> tells the viewer how many columns there are in the picture,
    //<height> tells the viewer how many rows, and
    //<max value of color> tells the viewer how to normalize the color values

    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;

        for (int i = 0; i < imageWidth; ++i) {
            color pixelColor(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0.25);
            std::cout<< pixelColor;
        }
    }

    std::cerr << "\nDone.\n";
}
