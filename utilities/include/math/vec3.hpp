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
		constexpr vec3() noexcept : m_e{0, 0, 0} {}
		constexpr vec3(Float e0, Float e1, Float e2) noexcept : m_e{e0, e1, e2} {}
		constexpr vec3(const color& c) noexcept : m_e{c.raw_r(), c.raw_b(), c.raw_g()} {}

		constexpr Float x() const {
			return m_e[0];
		}

		constexpr Float y() const {
			return m_e[1];
		}

		constexpr Float z() const {
			return m_e[2];
		}

		constexpr vec3 operator-() const {
			return vec3(-m_e[0], -m_e[1], -m_e[2]);
		}

		constexpr const Float& operator[](int i) const {
			return m_e[i];
		}

		constexpr Float& operator[](int i) {
			return m_e[i];
		}

		friend constexpr vec3& operator+=(vec3& u, const vec3& v) {
			u.m_e[0] += v.m_e[0];
			u.m_e[1] += v.m_e[1];
			u.m_e[2] += v.m_e[2];
			return u;
		}

		friend constexpr vec3& operator-=(vec3& u, const vec3& v) {
			u.m_e[0] -= v.m_e[0];
			u.m_e[1] -= v.m_e[1];
			u.m_e[2] -= v.m_e[2];
			return u;
		}

		friend constexpr vec3& operator*=(vec3& v, const Float t) {
			v.m_e[0] *= t;
			v.m_e[1] *= t;
			v.m_e[2] *= t;
			return v;
		}

		friend constexpr vec3& operator*=(const Float t, vec3& v) {
			return v *= t;
		}

		friend constexpr vec3& operator/=(vec3& v, const Float t) {
			return v *= (1 / t);
		}

		friend constexpr vec3 operator+(const vec3& u, const vec3& v) {
			vec3 copy = u;
			copy += v;
			return copy;
		}

		friend constexpr vec3 operator-(const vec3& u, const vec3& v) {
			vec3 copy = u;
			copy -= v;
			return copy;
		}

		friend constexpr vec3 operator*(const vec3& v, const Float t) {
			vec3 copy = v;
			copy *= t;
			return copy;
		}

		friend constexpr vec3 operator*(const Float t, const vec3& v) {
			vec3 copy = v;
			copy *= t;
			return copy;
		}

		friend constexpr vec3 operator/(const vec3& v, const Float t) {
			vec3 copy = v;
			copy /= t;
			return copy;
		}

		constexpr static Float dot(const vec3& u, const vec3& v) {
			return u.m_e[0] * v.m_e[0]
				 + u.m_e[1] * v.m_e[1]
				 + u.m_e[2] * v.m_e[2];
		}

		constexpr static vec3 cross(const vec3& u, const vec3& v) {
			return vec3(u.m_e[1] * v.m_e[2] - u.m_e[2] * v.m_e[1],
						u.m_e[2] * v.m_e[0] - u.m_e[0] * v.m_e[2],
						u.m_e[0] * v.m_e[1] - u.m_e[1] * v.m_e[0]);
		}

		constexpr static vec3 unitVector(vec3 v) {
			return v / v.length();
		}

		constexpr Float length() const {
			return std::sqrt(length_squared());
		}

		constexpr Float length_squared() const {
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

		constexpr bool nearZero() const {
			// Returns true if the vector is close to zero in all dimensions.
			const Float threshold = 1e-8;
			return (fabs(m_e[0]) < threshold) && (fabs(m_e[1]) < threshold) && (fabs(m_e[2]) < threshold);
		}

		constexpr static const vec3 reflect(const vec3& v, const vec3& normal) {
			return v - 2 * dot(v, normal) * normal;
		}

		constexpr static const vec3 refract(
			const vec3& incidentRay, const vec3& normal, Float refractiveIndexRatio) {
			Float cosTheta = dot(-incidentRay, normal);

			vec3 perpendicularComponent = refractiveIndexRatio * (incidentRay + cosTheta * normal);
			vec3 parallelComponent = -sqrt(1.0 - perpendicularComponent.length_squared()) * normal;
			return perpendicularComponent + parallelComponent;
		}

		static vec3 randomInUnitDisk() {
			while (true) {
				auto p = vec3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
				if (p.length_squared() >= 1) {
					continue;
				}
				return p;
			}
		}

		friend std::ostream& operator<<(std::ostream& out, const vec3& v) {
			out << v.m_e[0] << " " << v.m_e[1] << " " << v.m_e[2];
			return out;
		}

		//TODO: Change name of "unitVector" function to "normalize"
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
