#include "sphere.hpp"

bool sphere::hit(const ray& r, double t_min, double t_max, hitRecord& record) const {
    vec3 oc = r.origin() - m_center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - m_radius * m_radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
		return false;
	}

    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) /
        if (root < t_min || t_max < root)
            return false;
    }

    record.m_t = root;
    record.m_point = r.at(record.m_t);
    record.m_normal = (record.m_point - m_center) / m_radius;

    return true;
}
