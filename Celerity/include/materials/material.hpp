#pragma once

#include "hitRecord.hpp"
#include "utility.hpp"

class Material {
	public:
		virtual bool scatter(
			const ray& in, const HitRecord& record, color& attenuation, ray& scattered
		) const = 0;
};
