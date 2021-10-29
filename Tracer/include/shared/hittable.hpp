#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "hitRecord.hpp"
#include "ray.hpp"

class HittableObject {
	public:
		virtual bool hit(const ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};

#endif // HITTABLE_HPP
