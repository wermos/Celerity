#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <limits>
#include <ostream>
#include <random>
#include <numbers>

#include "float.hpp"

#include "color.hpp"

class vec3 {
	public:
		vec3() : m_e{0, 0, 0} {}
		vec3(Float e0, Float e1, Float e2) : m_e{e0, e1, e2} {}
		vec3(const color& c) : m_e{c.raw_r(), c.raw_b(), c.raw_g()} {}

		Float x() const {
			return m_e[0];
		}

		Float y() const {
			return m_e[1];
		}

		Float z() const {
			return m_e[2];
		}


		vec3 operator-() const {
			return vec3(-m_e[0], -m_e[1], -m_e[2]);
		}

		Float operator[](int i) const {
			return m_e[i];
		}

		Float& operator[](int i) {
			return m_e[i];
		}

		vec3& operator+=(const vec3& v) {
			m_e[0] += v.m_e[0];
			m_e[1] += v.m_e[1];
			m_e[2] += v.m_e[2];
			return *this;
		}

		vec3& operator*=(const Float t) {
			m_e[0] *= t;
			m_e[1] *= t;
			m_e[2] *= t;
			return *this;
		}

		vec3& operator/=(const Float t) {
			return *this *= (1 / t);
		}

		Float inline length() const {
			return std::sqrt(length_squared());
		}

		Float inline length_squared() const {
			return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
		}

		static const vec3 randomInUnitSphere() {
			// Generate theta and phi for spherical coordinates, and return
			// the Cartesian coordinates.

			// Spherical to Cartesian conversion: (r, theta, phi) -> (x, y, z)
			// x = r sin theta cos phi
			// y = r sin theta sin phi
			// z = r cos theta

			// Different from the book:
			// https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials
			Float thetaRad = randomFloat(0, 1) * std::numbers::pi;
			Float phiRad = randomFloat(0, 2) * std::numbers::pi;

#ifdef USE_DOUBLE_AS_FLOAT_TYPE
			return {sin(thetaRad) * cos(phiRad), sin(thetaRad) * sin(phiRad), cos(thetaRad)};
#else
			return {sinf(thetaRad) * cosf(phiRad), sinf(thetaRad) * sinf(phiRad), cosf(thetaRad)};
#endif
		}

		const bool nearZero() const {
			// Returns true if the vector is close to zero in all dimensions.
			const Float threshold = 1e-8;
			return (fabs(m_e[0]) < threshold) && (fabs(m_e[1]) < threshold) && (fabs(m_e[2]) < threshold);
		}

		static const vec3 reflect(const vec3& v, const vec3& normal) {
			return v - 2 * dot(v, normal) * normal;
		}

		static const vec3 refract(
			const vec3& incidentRay, const vec3& normal, Float refractiveIndexRatio) {
			Float cosTheta = dot(-incidentRay, normal);

			vec3 perpendicularComponent = refractiveIndexRatio * (incidentRay + cosTheta * normal);
			vec3 parallelComponent = -sqrt(1.0 - perpendicularComponent.length_squared()) * normal;
			return perpendicularComponent + parallelComponent;
		}

		friend std::ostream& operator<<(std::ostream& out, const vec3& v);

		friend vec3 operator+(const vec3& u, const vec3& v);

		friend vec3 operator-(const vec3& u, const vec3& v);

		friend vec3 operator*(const vec3& u, const vec3& v);
		friend vec3 operator*(Float t, const vec3& v);
		friend vec3 operator*(const vec3& v, Float t);

		friend vec3 operator/(vec3 v, Float t);

		friend Float dot(const vec3& u, const vec3& v);
		friend vec3 cross(const vec3& u, const vec3& v);

		friend vec3 unitVector(vec3 v);
		//TODO: Make operator implementations depend on each other
		//TODO: Change name of "unit_vector" function to "normalize"
	private:
		Float m_e[3];

		static const Float randomFloat(Float min, Float max) {
			// Returns a random real in [min, max].
			static std::uniform_real_distribution<Float> distribution(min, std::nextafter(max, std::numeric_limits<Float>::infinity()));
#ifdef USE_DOUBLE_AS_FLOAT_TYPE
			static std::mt19937_64 generator;
#else
			static std::mt19937 generator;
#endif

			return distribution(generator);
		}
};

// Type aliases for vec3
using point3 = vec3;    // 3D point

#endif // VEC3_HPP
