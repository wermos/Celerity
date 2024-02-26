#pragma once

// STL includes
#include <thread> // For std::thread
#include <atomic> // For std:atomic<T>
#include <syncstream> // For std::osyncstream

// Math includes
#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

// Object-related includes
#include "shapes/sphere.hpp"

#include "shared/hittable.hpp"
#include "shared/hittableList.hpp"

// Material-related includes
#include "materials/lambertian.hpp"
#include "materials/metal.hpp"

// Camera includes
#include "camera/camera.hpp"

// Utility includes
#include "shared/utility.hpp"

// Image writer includes
#include "imageWriters/ppmWriter.hpp"
#include "imageWriters/imageWriter.hpp"

namespace Renderer {
	void singleCoreRender(const int imageWidth, const int imageHeight,
						  const HittableList& world, const int maxRayDepth,
						  const Camera& camera, const int samplesPerPixel,
						  imageWriter& iw, ppmWriter& pw);
	
	void multiCoreRender(std::atomic<int>& scanLinesLeft, const int imageWidth,
						 const int imageHeight, const HittableList& world,
						 const int maxRayDepth, const Camera& camera, 
						 const int samplesPerPixel, imageWriter& iw);
}
