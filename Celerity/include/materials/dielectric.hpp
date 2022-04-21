#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include <cmath>

#include "float.hpp"

#include "hitRecord.hpp"
#include "material.hpp"

#include "color.hpp"

class Dielectric : public Material {
	public:
		constexpr Dielectric(Float refractiveIndex) noexcept
			: m_refractiveIndex(refractiveIndex) {}

		virtual bool scatter(
			const ray& in, const HitRecord& rec, color& attenuation, ray& scattered
		) const override;

	private:
		Float m_refractiveIndex;

		static Float reflectance(Float cosine, Float refractiveIndexRatio) {
			// Use Schlick's approximation for the Fresnel equations for reflectance.
			auto r_0 = (1 - refractiveIndexRatio) / (1 + refractiveIndexRatio);
			r_0 = r_0 * r_0;
			return r_0 + (1 - r_0) * std::pow((1 - cosine), 5);
		}
};

#endif // DIELECTRIC_HPP
