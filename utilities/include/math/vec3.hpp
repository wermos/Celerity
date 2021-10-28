#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>
#include <random>
#include <numbers>

#include "color.hpp"

class vec3 {
    public:
        vec3() : m_e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : m_e{e0, e1, e2} {}
		vec3(const color& c) : m_e{c.raw_r(), c.raw_b(), c.raw_g()} {}

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

        vec3& operator+=(const vec3& v) {
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

        double inline length() const {
            return std::sqrt(length_squared());
        }

        double inline length_squared() const {
            return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
        }

		static const vec3 randomInUnitSphere() {
			//Generate theta and phi for spherical coordinates, and return
			//the Cartesian coordinates.

			//Spherical to Cartesian conversion: (r, theta, phi) -> (x, y, z)
			// x = r sin theta cos phi
			// y = r sin theta sin phi
			// z = r cos theta

			//Different from the book:
			//https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials
			double thetaRad = randomDouble() * std::numbers::pi;
			double phiRad = randomDouble(0, 2) * std::numbers::pi;

			return {sin(thetaRad) * cos(phiRad), sin(thetaRad) * sin(phiRad), cos(thetaRad)};
		}

        friend std::ostream& operator<<(std::ostream& out, const vec3& v);

        friend vec3 operator+(const vec3& u, const vec3& v);

        friend vec3 operator-(const vec3& u, const vec3& v);

        friend vec3 operator*(const vec3& u, const vec3& v);
        friend vec3 operator*(double t, const vec3& v);
        friend vec3 operator*(const vec3& v, double t);

        friend vec3 operator/(vec3 v, double t);

        friend double dot(const vec3& u, const vec3& v);
        friend vec3 cross(const vec3& u, const vec3& v);

        friend vec3 unitVector(vec3 v);
        //TODO: Make operator implementations depend on each other
        //TODO: Change name of "unit_vector" function to "normalize"
    private:
        double m_e[3];

		static const double randomDouble(double min, double max) {
			// Returns a random real in [min,max).
			static std::uniform_real_distribution<double> distribution(min, max);
			static std::mt19937_64 generator;

			return distribution(generator);
		}

		static const double randomDouble() {
			// Returns a random real in [0,1).
			return randomDouble(0.0, 1.0);
		}
};

// Type aliases for vec3
using point3 = vec3;    // 3D point

#endif // VEC3_HPP
