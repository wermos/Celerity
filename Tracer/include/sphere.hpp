#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class Sphere : public HittableObject {
	public:

        Sphere(point3 center, double radius) : m_center(center), m_radius(radius) {};

        bool hit(
			const ray& r, double tMin, double tMax, HitRecord& rec) const override;

    private:
        point3 m_center;
        double m_radius;
};

#endif // SPHERE_HPP
