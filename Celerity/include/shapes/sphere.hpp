#pragma once

#include <memory>

#include "materials/material.hpp"
#include "ray.hpp"
#include "shared/hitRecord.hpp"
#include "shared/hittable.hpp"
#include "vec3.hpp"

class Sphere : public HittableObject {
   public:
    // No default constructor because this class is not default-constructible.

    Sphere(point3 center, float radius, std::shared_ptr<Material> material)
        : m_center(center), m_radius(radius), m_material(material) {}

    virtual bool hit(const ray& r, float tMin, float tMax,
                     HitRecord& rec) const override;

   private:
    point3 m_center;
    float m_radius;
    std::shared_ptr<Material> m_material;
};
