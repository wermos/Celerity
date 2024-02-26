// STL includes
#include <iostream> // For std::clog and std::cout
#include <thread> // For std::thread
#include <functional> // For std::ref and std::cref
#include <atomic> // For std:atomic<T>

// Camera includes
#include "camera.hpp"

// Renderer includes
#include "renderer.hpp"

// Image writer includes
#include "ppmWriter.hpp"
#include "imageWriter.hpp"

// STB Image include
#include "stb_image_library.hpp"

#include "float.hpp"

#include "vec3.hpp"

#include "scene.hpp"

int main() {
		// Image
		// constexpr Float aspectRatio = 16.0 / 9.0;
		constexpr std::size_t imageWidth = 640;
		constexpr std::size_t imageHeight = 480;
		constexpr Float aspectRatio = static_cast<Float>(imageWidth) / imageHeight;
		// constexpr std::size_t imageHeight = static_cast<std::size_t>(imageWidth / aspectRatio);
		constexpr std::size_t samplesPerPixel = 1;
		constexpr std::size_t maxRayDepth = 10;

		// World
		auto world = Scene::CornellSphere();

		// Camera
		// point3 lookFrom(13, 2, 3);
		// point3 lookAt(0, 0, 0);
		point3 lookFrom{0.0, 0.0, 0.0};
		point3 lookAt{0.0, 0.0, 1.0};
		vec3 viewUp(0, 1, 0);
		Float distanceToFocus = 5;
		Float aperture = 10;

		Camera camera(lookFrom, lookAt, viewUp, 30, aspectRatio, aperture, distanceToFocus);

		std::clog << "Finished scene initialization.\n";

		//Initialize file writers
		// TODO: Image writer API doesn't make sense fix it. One class should generate all types
		// of images.
		// Making a PPM while using multiple threads is a massive pain and not worth it.
		ppmWriter pw(imageWidth, imageHeight);
		imageWriter iw(imageWidth, imageHeight);

		// // Thread-related initializations
		// const auto numThreads = std::thread::hardware_concurrency();
		// auto threadPool = new std::thread[numThreads];
		// //This will be modified by multiple threads so it needs to be thread-safe
		// std::atomic<int> scanLinesLeft = imageHeight - 1;

		// std::clog << "Commencing ray tracing...";
		// // Kick off each thread with the Renderer::multiCoreRender() task
		// for (std::size_t i = 0; i < numThreads; ++i) {
		// 	threadPool[i] = std::thread(Renderer::multiCoreRender, std::ref(scanLinesLeft),
		// 								imageWidth, imageHeight, std::cref(world), maxRayDepth,
		// 								std::cref(camera), samplesPerPixel, std::ref(iw));
		// }

		// // Wait for all threads to finish their tasks
		// for (std::size_t i = 0; i < numThreads; ++i) {
		// 	threadPool[i].join();
		// }

		// delete[] threadPool;
		Renderer::singleCoreRender(
			imageWidth, imageHeight, world, maxRayDepth, camera,
			samplesPerPixel, iw, pw);

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
