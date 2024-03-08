// STL includes
#include <atomic>      // For std:atomic<T>
#include <cstddef>     // For std::size_t
#include <functional>  // For std::ref and std::cref
#include <thread>      // For std::thread

// Camera includes
#include "camera/camera.hpp"

// Scene includes
#include "scenes/scene.hpp"

// Renderer includes
#include "renderer/renderer.hpp"

// Image writer include
#include "imageWriters/imageWriter.hpp"

// STB Image include
#include "stb_image_library.hpp"

// spdlog include
#include "spdlog/spdlog.h"

#include "float.hpp"

int main() {
    // Image
    constexpr Float aspectRatio = 16.0 / 9.0;
    constexpr std::size_t imageWidth = 480;
    constexpr std::size_t imageHeight =
        static_cast<std::size_t>(imageWidth / aspectRatio);
    constexpr std::size_t samplesPerPixel = 30;
    constexpr std::size_t maxRayDepth = 15;

    // World
    const auto world = Scenes::randomScene();

    // Camera
    constexpr point3 lookFrom(13, 2, 3);
    constexpr point3 lookAt(0, 0, 0);
    constexpr vec3 viewUp(0, 1, 0);
    constexpr Float distanceToFocus = 10;
    constexpr Float aperture = 0.1;

    const Camera camera(lookFrom, lookAt, viewUp, 20, aspectRatio, aperture,
                  distanceToFocus);

    spdlog::info("Finished scene initialization.\n");

    // Initialize file writer
    ImageWriter iw(imageWidth, imageHeight);

    // Thread-related initializations
    const auto numThreads = std::thread::hardware_concurrency();
    const auto threadPool = new std::jthread[numThreads];
    // The variable  will be modified by multiple threads so it needs to be
    // thread-safe
    std::atomic<int> scanLinesLeft = imageHeight - 1;

    spdlog::info("Commencing ray tracing...");

    // Kick off each thread with the Renderer::multiCoreRender() task
    for (std::size_t i = 0; i < numThreads; ++i) {
        threadPool[i] =
            std::jthread(Renderer::multiCoreRender, std::ref(scanLinesLeft),
                         imageWidth, imageHeight, std::cref(world), maxRayDepth,
                         std::cref(camera), samplesPerPixel, std::ref(iw));
    }

    delete[] threadPool;

    spdlog::info('\n');

    // Write image file to disk
    if (iw.writePNG() == 0) {
        spdlog::info("PNG Image generated successfully.\n");
    } else {
        spdlog::error("An error occurred while generating the PNG image.\n");
    }

    if (iw.writeJPG() == 0) {
        spdlog::info("JPG Image generated successfully.\n");
    } else {
        spdlog::error("An error occurred while generating the JPG image.\n");
    }

    if (iw.writePPM() == 0) {
        spdlog::info("PPM Image generated successfully.\n");
    } else {
        spdlog::error("An error occurred while generating the PPM image.\n");
    }

    spdlog::info("Done.\n");
}
