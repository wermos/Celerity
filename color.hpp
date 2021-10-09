#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

class color {
    public:
        color() : m_color{0, 0, 0} {}
        color(double r, double g, double b) : m_color{r, g, b} {}

        double raw_r() const {
            return m_color[0];
        }

        double raw_g() const {
            return m_color[1];
        }

        double raw_b() const {
            return m_color[2];
        }

        int r(double max = 259.999) {
            return static_cast<int>(255.999 * m_color[0]);
        }

        int g(double max = 259.999) {
            return static_cast<int>(255.999 * m_color[1]);
        }

        int b(double max = 259.999) {
            return static_cast<int>(255.999 * m_color[2]);
        }

        // vec3 operator-() const {
        //     return vec3(-m_e[0], -m_e[1], -m_e[2]);
        // }

        // double operator[](int i) const {
        //     return m_e[i];
        // }

        // double& operator[](int i) {
        //     return m_e[i];
        // }

        // vec3& operator+=(const vec3& v) {
        //     m_e[0] += v.m_e[0];
        //     m_e[1] += v.m_e[1];
        //     m_e[2] += v.m_e[2];
        //     return *this;
        // }

        // vec3& operator*=(const double t) {
        //     m_e[0] *= t;
        //     m_e[1] *= t;
        //     m_e[2] *= t;
        //     return *this;
        // }

        // vec3& operator/=(const double t) {
        //     return *this *= (1 / t);
        // }

        // double length() const {
        //     return std::sqrt(length_squared());
        // }

        // double length_squared() const {
        //     return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
        // }

        friend std::ostream& operator<<(std::ostream& out, const color& v);

        // friend vec3 operator+(const vec3& u, const vec3& v);
        
        // friend vec3 operator-(const vec3& u, const vec3& v);
        
        // friend vec3 operator*(const vec3& u, const vec3& v);
        // friend vec3 operator*(double t, const vec3& v);
        // friend vec3 operator*(const vec3& v, double t);
        
        // friend vec3 operator/(vec3 v, double t);
    private:
        double m_color[3];
};

#endif // COLOR_HPP
