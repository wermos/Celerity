#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "hitRecord.hpp"

#include "material.hpp"

#include "color.hpp"

class Lambertian : public Material {
    public:
        Lambertian(const color& a) : m_albedo(a) {}

        virtual bool scatter(
            const ray& in, const HitRecord& record, color& attenuation, ray& scattered
        ) const override;

    public:
        color m_albedo;
};

#endif //LAMBERTIAN_HPP
