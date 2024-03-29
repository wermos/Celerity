#pragma once

#include <memory>

#include "ray.hpp"
#include "vec3.hpp"

class Material;

struct HitRecord {
    point3 point;
    vec3 normal;
    std::shared_ptr<Material> material;
    float t;
    bool frontFace;

    inline void setFaceNormal(const ray& r, const vec3& outwardNormal) {
        frontFace = vec3::dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
