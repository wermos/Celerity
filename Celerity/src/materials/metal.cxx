#include "metal.hpp"

#include "vec3.hpp"

bool Metal::scatter(const ray& in, const HitRecord& record, color& attenuation,
                    ray& scattered) const {
    vec3 reflected =
        vec3::reflect(vec3::unitVector(in.direction()), record.normal);

    scattered =
        ray(record.point, reflected + m_fuzz * vec3::randomInUnitSphere());
    attenuation = m_albedo;

    return (vec3::dot(scattered.direction(), record.normal) > 0);
}
