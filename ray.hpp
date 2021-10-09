#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction)
            : m_origin(origin), m_direction(direction)
        {}

        const point3 origin() const {
            return m_origin;
        }

        const vec3 direction() const {
            return m_direction;
        }

        const point3 at(double t) const {
            return m_origin + t * m_direction;
        }

    private:
        point3 m_origin;
        vec3 m_direction;
};

#endif // RAY_HPP
