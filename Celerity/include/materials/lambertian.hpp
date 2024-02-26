#pragma once

#include "float.hpp"

#include "hitRecord.hpp"
#include "material.hpp"

#include "color.hpp"

class Lambertian : public Material {
	public:
		constexpr Lambertian(const color& a) noexcept
			: m_albedo(a) {}

		virtual bool scatter(
			const ray& in, const HitRecord& record, color& attenuation, ray& scattered
		) const override;

	private:
		color m_albedo;
};
