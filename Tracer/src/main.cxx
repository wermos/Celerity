#include <iostream>

#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

#include "ppmWriter.hpp"

color rayColor(const ray& r) {
    vec3 unitDirection = unitVector(r.direction());
	//normalizing makes all the coordinates vary from [-1, 1] (inclusive)

    auto t = 0.5 * (unitDirection.y() + 1.0);
	//This is a trick to make the y value vary from [0, 1]

    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	//This is a linear combination of the start and end colors to make a
	//smooth and linear color gradient.
}

int main() {
    // Image
    constexpr auto aspectRatio = 16.0 / 9.0;
    constexpr int imageWidth = 400;
    constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // Camera
    constexpr auto viewportHeight = 2.0;
    constexpr auto viewportWidth = aspectRatio * viewportHeight;
    constexpr auto focalLength = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focalLength);

	//Initialize file writers
	ppmWriter pw(imageWidth, imageHeight);

    // Render
    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;

        for (int i = 0; i < imageWidth; ++i) {
			auto u = double(i) / (imageWidth - 1);
            auto v = double(j) / (imageHeight - 1);

            ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            color pixelColor = rayColor(r);

            pw.write(pixelColor);
        }
    }

    std::cerr << "\nDone.\n";
}
