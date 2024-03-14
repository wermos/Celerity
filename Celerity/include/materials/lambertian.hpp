#pragma once

#include "color.hpp"
#include "materials/material.hpp"
#include "shared/hitRecord.hpp"

class Lambertian : public Material {
   public:
    constexpr Lambertian(const color& a) noexcept : m_albedo(a) {}

    virtual bool scatter(const ray& in, const HitRecord& record,
                         color& attenuation, ray& scattered) const override;

   private:
    color m_albedo;
};
