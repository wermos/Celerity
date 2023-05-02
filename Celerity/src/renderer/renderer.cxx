#include "renderer.hpp"

namespace Renderer {
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

		vec3 unitDirection = vec3::unitVector(r.direction());
		//normalizing makes all the coordinates vary from [-1, 1] (inclusive)

		auto t = 0.5 * (unitDirection.y() + 1.0);
		//This is a trick to make the y value vary from [0, 1]

		return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
		//This is a linear combination of the start and end colors to make a
		//smooth and linear color gradient.
	}

	void singleCoreRender(const int imageWidth, const int imageHeight,
						  const HittableList& world, const int maxRayDepth,
						  const Camera& camera, const int samplesPerPixel,
						  ImageWriter& iw) {
		for (int j = imageHeight - 1; j >= 0; --j) {
			std::clog << "\rScanlines remaining: " << j << " " << std::flush;

			for (int i = 0; i < imageWidth; ++i) {
				color pixelColor;
				for (int s = 0; s < samplesPerPixel; ++s) {
					auto u = (i + randomDouble()) / (imageWidth - 1);
					auto v = (j + randomDouble()) / (imageHeight - 1);

					ray r = camera.getRay(u, v);

					pixelColor += rayColor(r, world, maxRayDepth);
				}

				pixelColor.combine(samplesPerPixel);

				iw.writeToImageBuffer(pixelColor);
			}
		}
	}

	void multiCoreRender(std::atomic<int>& scanLinesLeft, const int imageWidth,
						 const int imageHeight, const HittableList& world,
						 const int maxRayDepth, const Camera& camera,
						 const int samplesPerPixel, ImageWriter& iw) {
		while (scanLinesLeft >= 0) {
			int currentImageRow = scanLinesLeft;
			scanLinesLeft--;
			int bufferRow = imageHeight - currentImageRow - 1;

			std::osyncstream syncedLog(std::clog); //TODO: Make this optional.
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

				iw.writeToImageBuffer(3 * (bufferRow * imageWidth + i), pixelColor);
			}

		}
	}
} // Renderer namespace
