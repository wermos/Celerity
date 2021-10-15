#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

class color {
    public:
        color() : m_color{0, 0, 0} {}
        color(double r, double g, double b) : m_color{r, g, b} {}

        const double raw_r() const {
            return m_color[0];
        }

        const double raw_g() const {
            return m_color[1];
        }

        const double raw_b() const {
            return m_color[2];
        }

        const int r(double max = 259.999) const {
            return static_cast<int>(255.999 * m_color[0]);
        }

        const int g(double max = 259.999) const {
            return static_cast<int>(255.999 * m_color[1]);
        }

        const int b(double max = 259.999) const {
            return static_cast<int>(255.999 * m_color[2]);
        }

        // color operator-() const {
        //     return color(-m_e[0], -m_e[1], -m_e[2]);
        // }

        // double operator[](int i) const {
        //     return m_e[i];
        // }

        // double& operator[](int i) {
        //     return m_e[i];
        // }

        // color& operator+=(const color& v) {
        //     m_e[0] += v.m_e[0];
        //     m_e[1] += v.m_e[1];
        //     m_e[2] += v.m_e[2];
        //     return *this;
        // }

        // color& operator*=(const double t) {
        //     m_e[0] *= t;
        //     m_e[1] *= t;
        //     m_e[2] *= t;
        //     return *this;
        // }

        // color& operator/=(const double t) {
        //     return *this *= (1 / t);
        // }

        // double length() const {
        //     return std::sqrt(length_squared());
        // }

        // double length_squared() const {
        //     return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
        // }

        friend std::ostream& operator<<(std::ostream& out, const color& pixelColor);

        friend color operator+(const color& c1, const color& c2);

        // friend color operator-(const color& u, const color& v);

        // friend color operator*(const color& u, const color& v);
        friend color operator*(double t, const color& c);
        // friend color operator*(const color& v, double t);

        // friend color operator/(color v, double t);

		//TODO: Make operator implementations depend on each other
    private:
        double m_color[3];
};

#endif // COLOR_HPP
