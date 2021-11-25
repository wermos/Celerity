#include "lambertian.hpp"

#include "vec3.hpp"

bool Lambertian::scatter(
    const ray& in, const HitRecord& record, color& attenuation, ray& scattered
    ) const {
            auto scatterDirection = record.normal + vec3::randomInUnitSphere();
            scattered = ray(record.point, scatterDirection);
            attenuation = m_albedo;
            return true;
}
