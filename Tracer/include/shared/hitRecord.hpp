#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include <memory>

#include "vec3.hpp"
#include "ray.hpp"

class Material;

struct HitRecord {
    point3 point;
    vec3 normal;
	std::shared_ptr<Material> material;
    double t;
	bool frontFace;

    inline void setFaceNormal(const ray& r, const vec3& outwardNormal) {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

#endif // HIT_RECORD_HPP
