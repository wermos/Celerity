#pragma once

#include <cmath>

#include "color.hpp"
#include "materials/material.hpp"
#include "shared/hitRecord.hpp"

class Dielectric : public Material {
   public:
    constexpr Dielectric(float refractiveIndex) noexcept
        : m_refractiveIndex(refractiveIndex) {}

    virtual bool scatter(const ray& in, const HitRecord& rec,
                         color& attenuation, ray& scattered) const override;

   private:
    float m_refractiveIndex;

    static float reflectance(float cosine, float refractiveIndexRatio) {
        // Use Schlick's approximation for the Fresnel equations for
        // reflectance.
        auto r_0 = (1 - refractiveIndexRatio) / (1 + refractiveIndexRatio);
        r_0 *= r_0;
        return r_0 + (1 - r_0) * std::pow((1 - cosine), 5);
    }
};
