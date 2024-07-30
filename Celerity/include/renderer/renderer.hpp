#pragma once

// STL includes
#include <atomic>      // For std:atomic<T>

#include "shared/hittableList.hpp"

// Camera includes
#include "camera/camera.hpp"

// Image writer includes
#include "imageWriters/imageWriter.hpp"

#include "progressReporter.hpp"
namespace Renderer {
void singleCoreRender(const int imageWidth, const int imageHeight,
                      const HittableList& world, const int maxRayDepth,
                      const Camera& camera, const int samplesPerPixel,
                      ImageWriter& iw);

void multiCoreRender(std::atomic<int>& scanLinesLeft, const int imageWidth,
                     const int imageHeight, const HittableList& world,
                     const int maxRayDepth, const Camera& camera,
                     const int samplesPerPixel, ImageWriter& iw,
                     ProgressReporter& progressReporter);
}  // namespace Renderer
