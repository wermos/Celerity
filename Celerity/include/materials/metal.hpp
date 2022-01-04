#ifndef METAL_HPP
#define METAL_HPP

#include "float.hpp"

#include "hitRecord.hpp"
#include "material.hpp"

#include "color.hpp"


class Metal : public Material {
    public:
        Metal(const color& a) : m_albedo(a) {}

        virtual bool scatter(
            const ray& in, const HitRecord& record, color& attenuation, ray& scattered
        ) const override;

    public:
        color m_albedo;
};

#endif // METAL_HPP
