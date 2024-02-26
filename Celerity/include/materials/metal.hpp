#pragma once

#include "float.hpp"

#include "shared/hitRecord.hpp"
#include "materials/material.hpp"

#include "color.hpp"


class Metal : public Material {
	public:
		constexpr Metal(const color& a, Float fuzz) noexcept
			: m_albedo(a), m_fuzz(fuzz < 1 ? fuzz : 1) {}

		virtual bool scatter(
			const ray& in, const HitRecord& record, color& attenuation, ray& scattered
		) const override;

	private:
		color m_albedo;
		Float m_fuzz;
};
