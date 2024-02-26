// Object-related includes
#include "sphere.hpp"
#include "hittableList.hpp"

// Material-related includes
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"

#include "color.hpp"
#include "vec3.hpp"

#include "utility.hpp"

#include "scene.hpp"

#include <memory>

namespace Scenes {
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
}
