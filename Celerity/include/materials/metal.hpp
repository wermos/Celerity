#ifndef METAL_HPP
#define METAL_HPP

#include "float.hpp"

#include "hitRecord.hpp"
#include "material.hpp"

#include "color.hpp"


class Metal : public Material {
	public:
		Metal(const color& a, Float fuzz) : m_albedo(a), m_fuzz(fuzz < 1 ? fuzz : 1) {}

		virtual bool scatter(
			const ray& in, const HitRecord& record, color& attenuation, ray& scattered
		) const override;

	private:
		color m_albedo;
		Float m_fuzz;
};

#endif // METAL_HPP
