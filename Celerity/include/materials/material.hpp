#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "hitRecord.hpp"
#include "utility.hpp"

class Material {
   public:
    virtual bool scatter(const ray& in, const HitRecord& record,
                         color& attenuation, ray& scattered) const = 0;
};

#endif  // MATERIAL_HPP
