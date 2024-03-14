#pragma once

#include "ray.hpp"
#include "shared/hitRecord.hpp"

class HittableObject {
   public:
    virtual bool hit(const ray& r, float tMin, float tMax,
                     HitRecord& rec) const = 0;
};
