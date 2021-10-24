#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <concepts>

#include "ray.hpp"

struct hitRecord {
    point3 m_point;
    vec3 m_normal;
    double m_t;
	bool m_frontFace;

    inline void setFaceNormal(const ray& r, const vec3& outwardNormal) {
        m_frontFace = dot(r.direction(), outwardNormal) < 0;
        m_normal = m_frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittableObject {
	public:
		virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const = 0;
};

#endif // HITTABLE_HPP
