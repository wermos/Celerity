#include "sphere.hpp"

bool Sphere::hit(const ray& r, double tMin, double tMax, HitRecord& record) const {
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
    if (root < tMin || tMax < root) {
        root = (-half_b + sqrtd) / a;
        if (root < tMin || tMax < root) {
            return false;
		}
    }

    record.t = root;
    record.point = r.at(record.t);

	vec3 outwardNormal = (record.point - m_center) / m_radius;
    record.setFaceNormal(r, outwardNormal);
	record.material = m_material;

    return true;
}
