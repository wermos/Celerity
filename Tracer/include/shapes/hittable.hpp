#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <memory>

#include "ray.hpp"
#include "material.hpp"

//This goes inside the shapes directory because it defines an interface for shapes

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

class HittableObject {
	public:
		virtual bool hit(const ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};

#endif // HITTABLE_HPP
