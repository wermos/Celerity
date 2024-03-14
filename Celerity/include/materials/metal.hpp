#pragma once

#include "color.hpp"
#include "materials/material.hpp"
#include "shared/hitRecord.hpp"

class Metal : public Material {
   public:
    constexpr Metal(const color& a, float fuzz) noexcept
        : m_albedo(a), m_fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(const ray& in, const HitRecord& record,
                         color& attenuation, ray& scattered) const override;

   private:
    color m_albedo;
    float m_fuzz;
};
