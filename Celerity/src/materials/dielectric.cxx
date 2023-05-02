#include "dielectric.hpp"

#include "vec3.hpp"

bool Dielectric::scatter(const ray& in, const HitRecord& record,
                         color& attenuation, ray& scattered) const {
    attenuation = color(1.0, 1.0, 1.0);
    Float refractionRatio =
        record.frontFace ? (1.0 / m_refractiveIndex) : m_refractiveIndex;

    vec3 unitDirection = vec3::unitVector(in.direction());
    Float cosTheta = vec3::dot(-unitDirection, record.normal);
    Float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    vec3 direction;

    if (cannotRefract ||
        reflectance(cosTheta, refractionRatio) > randomDouble()) {
        // The idea behind the second condition is that, if the reflectance is r
        // (where 0 <= r <= 1), then we have to reflect the ray 100 * r% of the
        // time. To achieve this, we take a Monte Carlo approach and generate
        // random doubles to compare with. For example, if r = 0.2, then we must
        // reflect the ray 20% of the time.
        direction = vec3::reflect(unitDirection, record.normal);
    } else {
        direction =
            vec3::refract(unitDirection, record.normal, refractionRatio);
    }

    scattered = ray(record.point, direction);
    return true;
}
