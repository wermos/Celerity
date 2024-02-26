#include "scene.hpp"

// Object-related includes
#include "sphere.hpp"
#include "hittableList.hpp"

// Material-related includes
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"

#include "ray.hpp"
#include "vec3.hpp"
#include "color.hpp"

#include <memory>

namespace Scene {
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

	HittableList CornellSphere() {
		HittableList builder;

		// Materials
		auto diffuse_grey_mat = std::make_shared<Lambertian>(color(0.7, 0.7, 0.7));
		auto diffuse_red_mat = std::make_shared<Lambertian>(color(3.0, 0.25, 0.25));
		auto diffuse_blue_mat = std::make_shared<Lambertian>(color(0.25, 0.25, 3.0));
		auto diffuse_black_mat = std::make_shared<Lambertian>(color());
		
		auto glass_mat = std::make_shared<Dielectric>(1.5);
		// Honestly don't know what params mirror has
		auto mirror_mat = std::make_shared<Metal>(color(1.0), 0.0);

		// Objects		
		// Cornell scene with spheres
		auto left = std::make_shared<Sphere>(point3{100060, 50, 0}, 1e5, diffuse_red_mat);
		auto right = std::make_shared<Sphere>(point3{-100050, 50, -50}, 1e5, diffuse_blue_mat);
		auto back = std::make_shared<Sphere>(point3{0, 50, -100050}, 1e5, diffuse_black_mat);
		auto front = std::make_shared<Sphere>(point3{0, 50, 100180}, 1e5, diffuse_grey_mat);
		auto bottom = std::make_shared<Sphere>(point3{7, -100036.5, 100}, 1e5, diffuse_grey_mat);
		auto top = std::make_shared<Sphere>(point3{7, 100070.5, 100}, 1e5, diffuse_blue_mat);
		auto mirror_sphere = std::make_shared<Sphere>(point3{-20, -20, 120}, 16.5, mirror_mat);
		auto glass_sphere = std::make_shared<Sphere>(point3{30, -20, 150}, 16.5, glass_mat);

		builder.add(left);
		builder.add(right);
		builder.add(back);
		builder.add(front);
		builder.add(bottom);
		builder.add(top);
		builder.add(mirror_sphere);
		builder.add(glass_sphere);

		return builder;
	}
}
