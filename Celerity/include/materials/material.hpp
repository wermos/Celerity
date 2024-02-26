#pragma once

#include "shared/hitRecord.hpp"
#include "shared/utility.hpp"

class Material {
	public:
		virtual bool scatter(
			const ray& in, const HitRecord& record, color& attenuation, ray& scattered
		) const = 0;
};
