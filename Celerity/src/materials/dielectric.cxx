#include "dielectric.hpp"

#include "vec3.hpp"

bool Dielectric::scatter(
	const ray& in, const HitRecord& record, color& attenuation, ray& scattered
		) const {
	attenuation = color(1.0, 1.0, 1.0);
	Float refractionRatio = record.frontFace ? (1.0 / m_refractiveIndex) : m_refractiveIndex;

	vec3 unitDirection = unitVector(in.direction());
	Float cosTheta = dot(-unitDirection, record.normal);
	Float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0;
	vec3 direction;

	if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble()) {
		direction = vec3::reflect(unitDirection, record.normal);
	} else {
		direction = vec3::refract(unitDirection, record.normal, refractionRatio);
	}

	scattered = ray(record.point, direction);
	return true;
}
