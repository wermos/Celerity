#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class sphere requires HittableObject<sphere> {
	public:
		sphere() = default;

        sphere(point3 center, double radius) : m_center(center), m_radius(radius)
		{}

        bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const;

    private:
        point3 m_center;
        double m_radius;
};

#endif // SPHERE_HPP
