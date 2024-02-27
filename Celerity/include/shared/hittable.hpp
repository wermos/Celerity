#pragma once

#include "float.hpp"
#include "ray.hpp"
#include "shared/hitRecord.hpp"

class HittableObject {
   public:
    virtual bool hit(const ray& r, Float tMin, Float tMax,
                     HitRecord& rec) const = 0;
};
