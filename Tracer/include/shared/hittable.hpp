#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "float.hpp"

#include "hitRecord.hpp"
#include "ray.hpp"

class HittableObject {
	public:
		virtual bool hit(const ray& r, Float tMin, Float tMax, HitRecord& rec) const = 0;
};

#endif // HITTABLE_HPP
