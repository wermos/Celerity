#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <memory>

#include "float.hpp"

#include "hittable.hpp"
#include "hitRecord.hpp"

#include "material.hpp"

#include "vec3.hpp"
#include "ray.hpp"

class Sphere : public HittableObject {
	public:
		// No default constructor because this class is not default-constructible.

        Sphere(point3 center, Float radius, std::shared_ptr<Material> material) :
			m_center(center), m_radius(radius), m_material(material) {}

        virtual bool hit(
			const ray& r, Float tMin, Float tMax, HitRecord& rec) const override;

    private:
        point3 m_center;
        Float m_radius;
		std::shared_ptr<Material> m_material;
};

#endif // SPHERE_HPP
