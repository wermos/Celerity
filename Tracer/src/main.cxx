// STL includes
#include <iostream> // For std::cerr and std::cout
#include <thread> // For std::thread
#include <functional> // For std::ref and std::cref
#include <atomic> // For std:atomic<T>
#include <syncstream> // For std::osyncstream

// Math includes
#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

// Object-related includes
#include "hittable.hpp"
#include "sphere.hpp"
#include "hittableList.hpp"

// Material-related includes
//#include "material.hpp"
#include "lambertian.hpp"
#include "metal.hpp"

// Camera includes
#include "camera.hpp"

// Utility includes
#include "utility.hpp"

// Image writer includes
#include "ppmWriter.hpp"
#include "imageWriter.hpp"

// Profiling includes
#include "instrumentor.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

color rayColor(const ray& r, const HittableList& world, int depth) {
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0) {
		return color(0, 0, 0);
	}

	HitRecord record;

	if (world.hit(r, 0.001, infinity, record)) {
		//TODO: Investigate whether it is worth it to make the tolerance customizable.
		ray scattered;
		color attenuation;

		if (record.material->scatter(r, record, attenuation, scattered)) {
			return attenuation * rayColor(scattered, world, depth - 1);
		}

		return color(0, 0, 0);
	}

	vec3 unitDirection = unitVector(r.direction());
	//normalizing makes all the coordinates vary from [-1, 1] (inclusive)

	auto t = 0.5 * (unitDirection.y() + 1.0);
	//This is a trick to make the y value vary from [0, 1]

	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	//This is a linear combination of the start and end colors to make a
	//smooth and linear color gradient.
}

void render(std::atomic<int>& scanLinesLeft, const int imageWidth, const int imageHeight,
			const HittableList& world, const int maxRayDepth, const Camera& camera,
			const int samplesPerPixel, imageWriter& iw) {
	while (scanLinesLeft >= 0) {
		int currentImageRow = scanLinesLeft;
		scanLinesLeft--;
		int bufferRow = imageHeight - currentImageRow - 1;

		std::osyncstream syncedLog(std::clog);
		syncedLog << "\rScanlines remaining: " << currentImageRow << " " << std::flush;

		for (int i = 0; i < imageWidth; ++i) {
			color pixelColor;
			for (int s = 0; s < samplesPerPixel; ++s) {
				auto u = (i + randomDouble()) / (imageWidth - 1);
				auto v = (currentImageRow + randomDouble()) / (imageHeight - 1);

				ray r = camera.getRay(u, v);

				pixelColor += rayColor(r, world, maxRayDepth);
			}

			pixelColor.combine(samplesPerPixel);

			iw.writeToJPGBuffer(3 * (bufferRow * imageWidth + i), pixelColor);
			iw.writeToPNGBuffer(3 * (bufferRow * imageWidth + i), pixelColor);
		}

	}
}

int main() {
	Instrumentor::get().beginSession("main");
	{
		PROFILE_FUNCTION();

		// Image
		constexpr auto aspectRatio = 16.0 / 9.0;
		constexpr int imageWidth = 1920;
		constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
		constexpr int samplesPerPixel = 100;
		constexpr int maxRayDepth = 50;

		// World
		HittableList world;

		auto groundMaterial = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
		auto centerMaterial = std::make_shared<Lambertian>(color(0.7, 0.3, 0.3));
		auto leftMaterial   = std::make_shared<Metal>(color(0.8, 0.8, 0.8));
		auto rightMaterial  = std::make_shared<Metal>(color(0.8, 0.6, 0.2));

		world.add(std::make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, groundMaterial));
		world.add(std::make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, centerMaterial));
		world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, leftMaterial));
		world.add(std::make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, rightMaterial));

		// Camera
		Camera camera;

		//Initialize file writers
		// Making a PPM while using multiple threads is a massive pain and not worth it.
		// ppmWriter pw(imageWidth, imageHeight);
		imageWriter iw(imageWidth, imageHeight);

		// Thread-related initializations
		const auto numThreads = std::thread::hardware_concurrency();
		auto threadPool = new std::thread[numThreads];
		//This will be modified by multiple threads so it needs to be thread-safe
		std::atomic<int> scanLinesLeft = imageHeight - 1;

		// Kick off each thread with the render() task
		for (int i = 0; i < numThreads; ++i) {
			threadPool[i] = std::thread(render, std::ref(scanLinesLeft), imageWidth, imageHeight,
										std::cref(world), maxRayDepth, std::cref(camera),
										samplesPerPixel, std::ref(iw));
		}

		// Wait for all threads to finish their tasks
		for (int i = 0; i < numThreads; ++i) {
			threadPool[i].join();
		}

		delete[] threadPool;

		std::clog << "\n";

		// Write image file to disk
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

		std::clog << "Done.\n";
	}
	Instrumentor::get().endSession();
}
