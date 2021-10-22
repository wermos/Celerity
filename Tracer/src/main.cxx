#include <iostream>

#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

#include "ppmWriter.hpp"
#include "imageWriter.hpp"

#include "instrumentor.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

double hitSphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

color rayColor(const ray& r) {
    auto t = hitSphere(point3(0, 0, -1), 0.5, r);
	//The value of t at which the ray hits the sphere.
    if (t > 0.0) {
        vec3 N = unitVector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unitDirection = unitVector(r.direction());
	//normalizing makes all the coordinates vary from [-1, 1] (inclusive)

    t = 0.5 * (unitDirection.y() + 1.0);
	//This is a trick to make the y value vary from [0, 1]

    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	//This is a linear combination of the start and end colors to make a
	//smooth and linear color gradient.
}

int main() {
	Instrumentor::get().beginSession("main");
	{
	PROFILE_FUNCTION();

    // Image
    constexpr auto aspectRatio = 16.0 / 9.0;
    constexpr int imageWidth = 1920;
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
	imageWriter iw(imageWidth, imageHeight);

    // Render
    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;

        for (int i = 0; i < imageWidth; ++i) {
			auto u = double(i) / (imageWidth - 1);
            auto v = double(j) / (imageHeight - 1);

            ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            color pixelColor = rayColor(r);

            pw.write(pixelColor);
			iw.writeToPNG(pixelColor);
			iw.writeToJPG(pixelColor);
        }
    }

	std::cerr << "\n";

	if (iw.writePNG() != 0) {
		std::cout << "PNG Image generated successfully.\n";
	} else {
		std::cout << "An error occurred while generating the PNG image.\n";
	}

	if (iw.writeJPG() != 0) {
		std::cout << "JPG Image generated successfully.\n";
	} else {
		std::cout << "An error occurred while generating the JPG image.\n";
	}

    std::cerr << "Done.\n";
	}
	Instrumentor::get().endSession();
}
