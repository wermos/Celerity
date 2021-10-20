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

// Using a concept instead of an abstract class to reduce runtime overhead.
template <typename T>
concept HittableObject =
	requires (T object, const ray& r, double t_min, double t_max, hitRecord& rec) {
		{ object.hit(r, t_min, t_max, rec) } -> std::convertible_to<bool>;
		// Way of writing the concept shamelessly lifted from here:
		// https://en.cppreference.com/w/cpp/language/constraints
	};

#endif // HITTABLE_HPP
