#ifndef RENDERER_HPP
#define RENDERER_HPP

// STL includes
#include <thread> // For std::thread
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
#include "lambertian.hpp"
#include "metal.hpp"

// Camera includes
#include "camera.hpp"

// Utility includes
#include "utility.hpp"

// Image writer includes
#include "imageWriter.hpp"

namespace Renderer {
	void singleCoreRender(const int imageWidth, const int imageHeight,
						  const HittableList& world, const int maxRayDepth,
						  const Camera& camera, const int samplesPerPixel,
						  ImageWriter& iw);
	
	void multiCoreRender(std::atomic<int>& scanLinesLeft, const int imageWidth,
						 const int imageHeight, const HittableList& world,
						 const int maxRayDepth, const Camera& camera, 
						 const int samplesPerPixel, ImageWriter& iw);
}
#endif // RENDERER_HPP