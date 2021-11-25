#include "vec3.hpp"
// vec3 Utility Functions

std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.m_e[0] << " " << v.m_e[1] << " " << v.m_e[2];
}

vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.m_e[0] + v.m_e[0], u.m_e[1] + v.m_e[1], u.m_e[2] + v.m_e[2]);
}

vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.m_e[0] - v.m_e[0], u.m_e[1] - v.m_e[1], u.m_e[2] - v.m_e[2]);
}

vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.m_e[0] * v.m_e[0], u.m_e[1] * v.m_e[1], u.m_e[2] * v.m_e[2]);
}

vec3 operator*(Float t, const vec3& v) {
    return vec3(t * v.m_e[0], t * v.m_e[1], t * v.m_e[2]);
}

vec3 operator*(const vec3& v, Float t) {
    return t * v;
}

vec3 operator/(vec3 v, Float t) {
    return (1 / t) * v;
}

Float dot(const vec3& u, const vec3& v) {
    return u.m_e[0] * v.m_e[0]
         + u.m_e[1] * v.m_e[1]
         + u.m_e[2] * v.m_e[2];
}

vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.m_e[1] * v.m_e[2] - u.m_e[2] * v.m_e[1],
                u.m_e[2] * v.m_e[0] - u.m_e[0] * v.m_e[2],
                u.m_e[0] * v.m_e[1] - u.m_e[1] * v.m_e[0]);
}

vec3 unitVector(vec3 v) {
    return v / v.length();
}
