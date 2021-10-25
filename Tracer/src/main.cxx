#include <iostream>

#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

#include "hittable.hpp"
#include "sphere.hpp"
#include "hittableList.hpp"
#include "utility.hpp"

#include "ppmWriter.hpp"
#include "imageWriter.hpp"

#include "instrumentor.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

color rayColor(const ray& r, const HittableList& world) {
	HitRecord record;

	if (world.hit(r, 0, infinity, record)) {
		vec3 temp = 0.5 * (record.normal + color(1,1,1));
        return {temp.x(), temp.y(), temp.z()};
    }

    vec3 unitDirection = unitVector(r.direction());
	//normalizing makes all the coordinates vary from [-1, 1] (inclusive)

    auto t = 0.5 * (unitDirection.y() + 1.0);
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

		// World
    	HittableList world;
    	world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    	world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

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
				color pixelColor = rayColor(r, world);

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
