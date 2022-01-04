#include "metal.hpp"

#include "vec3.hpp"

bool Metal::scatter(
    	const ray& in, const HitRecord& record, color& attenuation, ray& scattered
    ) const {
	vec3 reflected = vec3::reflect(unitVector(in.direction()), record.normal);

	scattered = ray(record.point, reflected);
	attenuation = m_albedo;

	return (dot(scattered.direction(), record.normal) > 0);
}
