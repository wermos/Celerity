// STL includes
#include <iostream> // For std::clog and std::cout
#include <thread> // For std::thread
#include <functional> // For std::ref and std::cref
#include <atomic> // For std:atomic<T>

// Object-related includes
#include "sphere.hpp"
#include "hittableList.hpp"

// Material-related includes
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"

// Camera includes
#include "camera.hpp"

// Renderer includes
#include "renderer.hpp"

// Image writer includes
#include "ppmWriter.hpp"
#include "imageWriter.hpp"

// STB Image include
#include "stb_image_library.hpp"

HittableList randomScene() {
	HittableList world;

	auto groundMaterial = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, groundMaterial));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto chooseMaterial = randomDouble();
			point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<Material> sphereMaterial;

				if (chooseMaterial < 0.8) {
					// diffuse material
					auto albedo = color::random() * color::random();
					sphereMaterial = std::make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				} else if (chooseMaterial < 0.95) {
					// metal material
					auto albedo = color::random(0.5, 1);
					auto fuzz = randomDouble(0, 0.5);
					sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				} else {
					// glass material
					sphereMaterial = std::make_shared<Dielectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}


int main() {
		// Image
		constexpr Float aspectRatio = 16.0 / 9.0;
		constexpr std::size_t imageWidth = 1920;
		constexpr std::size_t imageHeight = static_cast<std::size_t>(imageWidth / aspectRatio);
		constexpr std::size_t samplesPerPixel = 500;
		constexpr std::size_t maxRayDepth = 50;

		// World
		auto world = randomScene();

		// Camera
		point3 lookFrom(13, 2, 3);
		point3 lookAt(0, 0, 0);
		vec3 viewUp(0, 1, 0);
		Float distanceToFocus = 10;
		Float aperture = 0.1;

		Camera camera(lookFrom, lookAt, viewUp, 20, aspectRatio, aperture, distanceToFocus);

		std::clog << "Finished scene initialization.\n";

		//Initialize file writers
		// TODO: Image writer API doesn't make sense fix it. One class should generate all types
		// of images.
		// Making a PPM while using multiple threads is a massive pain and not worth it.
		// ppmWriter pw(imageWidth, imageHeight);
		imageWriter iw(imageWidth, imageHeight);

		// Thread-related initializations
		const auto numThreads = std::thread::hardware_concurrency();
		auto threadPool = new std::thread[numThreads];
		//This will be modified by multiple threads so it needs to be thread-safe
		std::atomic<int> scanLinesLeft = imageHeight - 1;

		std::clog << "Commencing ray tracing...";
		// Kick off each thread with the Renderer::multiCoreRender() task
		for (std::size_t i = 0; i < numThreads; ++i) {
			threadPool[i] = std::thread(Renderer::multiCoreRender, std::ref(scanLinesLeft),
										imageWidth, imageHeight, std::cref(world), maxRayDepth,
										std::cref(camera), samplesPerPixel, std::ref(iw));
		}

		// Wait for all threads to finish their tasks
		for (std::size_t i = 0; i < numThreads; ++i) {
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
