// STL includes
#include <atomic>      // For std:atomic<T>
#include <functional>  // For std::ref and std::cref
#include <iostream>    // For std::clog and std::cout
#include <thread>      // For std::thread

// Camera includes
#include "camera.hpp"

// Scene includes
#include "manySpheres.hpp"

// Renderer includes
#include "renderer.hpp"

// Image writer includes
#include "imageWriter.hpp"

int main() {
    // Image
    constexpr Float aspectRatio = 16.0 / 9.0;
    constexpr std::size_t imageWidth = 1920;
    constexpr std::size_t imageHeight =
        static_cast<std::size_t>(imageWidth / aspectRatio);
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

    Camera camera(lookFrom, lookAt, viewUp, 20, aspectRatio, aperture,
                  distanceToFocus);

    std::clog << "Finished scene initialization.\n";

    // Initialize file writers
    ImageWriter iw(imageWidth, imageHeight);

    // Thread-related initializations
    const auto numThreads = std::thread::hardware_concurrency();
    auto threadPool = new std::thread[numThreads];
    // This will be modified by multiple threads so it needs to be thread-safe
    std::atomic<int> scanLinesLeft = imageHeight - 1;

    std::clog << "Commencing ray tracing...";
    // Kick off each thread with the Renderer::multiCoreRender() task
    for (std::size_t i = 0; i < numThreads; ++i) {
        threadPool[i] =
            std::thread(Renderer::multiCoreRender, std::ref(scanLinesLeft),
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
    iw.writeToPNGFile();
    iw.writeToJPGFile();

    std::clog << "Done.\n";
}
