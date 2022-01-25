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

// Profiling includes
#include "instrumentor.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
		// Image
		constexpr auto aspectRatio = 16.0 / 9.0;
		constexpr std::size_t imageWidth = 1920;
		constexpr std::size_t imageHeight = static_cast<std::size_t>(imageWidth / aspectRatio);
		constexpr std::size_t samplesPerPixel = 100;
		constexpr std::size_t maxRayDepth = 50;

		// World
		HittableList world;

		auto groundMaterial = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
		auto centerMaterial = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
		auto leftMaterial   = std::make_shared<Dielectric>(1.5);
		auto rightMaterial  = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);

		world.add(std::make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, groundMaterial));
		world.add(std::make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, centerMaterial));
		world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, leftMaterial));
		world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),  -0.4, leftMaterial));
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

		// Kick off each thread with the Renderer::multiCoreRender() task
		for (auto i = 0; i < numThreads; ++i) {
			threadPool[i] = std::thread(Renderer::multiCoreRender, std::ref(scanLinesLeft),
										imageWidth, imageHeight, std::cref(world), maxRayDepth,
										std::cref(camera), samplesPerPixel, std::ref(iw));
		}

		// Wait for all threads to finish their tasks
		for (auto i = 0; i < numThreads; ++i) {
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
