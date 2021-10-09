#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

class vec3 {
    public:
        vec3() : m_e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : m_e{e0, e1, e2} {}

        double x() const {
            return m_e[0];
        }

        double y() const {
            return m_e[1];
        }

        double z() const {
            return m_e[2];
        }


        vec3 operator-() const {
            return vec3(-m_e[0], -m_e[1], -m_e[2]);
        }

        double operator[](int i) const {
            return m_e[i];
        }

        double& operator[](int i) {
            return m_e[i];
        }

        vec3& operator+=(const vec3 &v) {
            m_e[0] += v.m_e[0];
            m_e[1] += v.m_e[1];
            m_e[2] += v.m_e[2];
            return *this;
        }

        vec3& operator*=(const double t) {
            m_e[0] *= t;
            m_e[1] *= t;
            m_e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) {
            return *this *= (1 / t);
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const {
            return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
        }

    private:
        double m_e[3];
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

#endif // VEC3_HPP