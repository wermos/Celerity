#pragma once

/* STL includes */
#include <cmath>
#include <limits>
#include <ostream>
#include <random>
#include <numbers>
#include <type_traits>

/* color header include */
#include "color.hpp"

#include <immintrin.h>

// It needs to be aligned on 128-bit boundaries because we are going to load the components into
// SSE registers for addition and stuff
class alignas(16) vec3 {
	public:
		constexpr vec3() noexcept : m_e{0, 0, 0} {}
		constexpr vec3(float e0, float e1, float e2) noexcept : m_e{e0, e1, e2} {}
		constexpr vec3(const color& c) noexcept : m_e{c.raw_r(), c.raw_b(), c.raw_g()} {}

		constexpr float x() const {
			return m_e[0];
		}

		constexpr float y() const {
			return m_e[1];
		}

		constexpr float z() const {
			return m_e[2];
		}

		constexpr vec3 operator-() const {
			if (std::is_constant_evaluated()) {
				// constexpr branch
				return {-m_e[0], -m_e[1], -m_e[2]};
			} else {
				// runtime branch

				__m128 data = _mm_load_ps(m_e);

				// Create a __m128 with all bits set to represent -0.0f
				__m128 negZero = _mm_set1_ps(-0.0f);

				// Negate the data
				__m128 negData = _mm_xor_ps(data, negZero);


				// auto op = xsimd::batch<float, xsimd::sse4_2>::load_aligned(m_e);

				// return {xsimd::neg(op)};
				return {negData};
			}
		}

		constexpr const float& operator[](int i) const {
			return m_e[i];
		}

		constexpr float& operator[](int i) {
			return m_e[i];
		}

		friend constexpr vec3& operator+=(vec3& u, const vec3& v) {
			if (std::is_constant_evaluated()) {
				// constexpr branch
				u.m_e[0] += v.m_e[0];
				u.m_e[1] += v.m_e[1];
				u.m_e[2] += v.m_e[2];
			} else {
				// runtime branch

				__m128 op1 = _mm_load_ps(u.m_e);
				__m128 op2 = _mm_load_ps(v.m_e);
				// auto op1 = xsimd::batch<float, xsimd::sse4_2>::load_aligned(u.m_e);
				// auto op2 = xsimd::batch<float, xsimd::sse4_2>::load_aligned(v.m_e);

				// op1 += op2;

				// op1.store_aligned(u.m_e);

				op1 = _mm_add_ps(op1, op2);
				_mm_store_ps(u.m_e, op1);

			}

			return u;
		}

		friend constexpr vec3& operator-=(vec3& u, const vec3& v) {
			if (std::is_constant_evaluated()) {
				// constexpr branch
				u.m_e[0] -= v.m_e[0];
				u.m_e[1] -= v.m_e[1];
				u.m_e[2] -= v.m_e[2];
			} else {
				// runtime branch

				__m128 op1 = _mm_load_ps(u.m_e);
				__m128 op2 = _mm_load_ps(v.m_e);
				// auto op1 = xsimd::batch<float, xsimd::sse4_2>::load_aligned(u.m_e);
				// auto op2 = xsimd::batch<float, xsimd::sse4_2>::load_aligned(v.m_e);

				// op1 -= op2;

				// op1.store_aligned(u.m_e);

				op1 = _mm_sub_ps(op1, op2);
				_mm_store_ps(u.m_e, op1);
			}

			return u;
		}

		friend constexpr vec3& operator*=(vec3& v, const float t) {
			if (std::is_constant_evaluated()) {
				// constexpr branch
				v.m_e[0] *= t;
				v.m_e[1] *= t;
				v.m_e[2] *= t;
			} else {
				// runtime branch

				__m128 op1 = _mm_set1_ps(t);
				__m128 op2 = _mm_load_ps(v.m_e);
				// xsimd::batch<float, xsimd::sse4_2> op1(t);
				// auto op2 = xsimd::batch<float, xsimd::sse4_2>::load_aligned(v.m_e);

				// op1 *= op2;

				// op1.store_aligned(v.m_e);

				op1 = _mm_mul_ps(op1, op2);

				_mm_store_ps(v.m_e, op1);
			}

			return v;
		}

		friend constexpr vec3& operator*=(const float t, vec3& v) {
			return v *= t;
		}

		friend constexpr vec3& operator/=(vec3& v, const float t) {
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

		friend constexpr vec3 operator*(const vec3& v, const float t) {
			vec3 copy = v;
			copy *= t;
			return copy;
		}

		friend constexpr vec3 operator*(const float t, const vec3& v) {
			vec3 copy = v;
			copy *= t;
			return copy;
		}

		friend constexpr vec3 operator/(const vec3& v, const float t) {
			vec3 copy = v;
			copy /= t;
			return copy;
		}

		// constexpr static float dot(const vec3& u, const vec3& v) {
		constexpr static float dot(const vec3& u, const vec3& v) {
			if (std::is_constant_evaluated()) {
			// 	// constexpr branch
				return u.m_e[0] * v.m_e[0]
					 + u.m_e[1] * v.m_e[1]
					 + u.m_e[2] * v.m_e[2];
			} else {
				// runtime branch
				__m128 r1 = _mm_load_ps(u.m_e);
				__m128 r2 = _mm_load_ps(v.m_e);

				// __m128 temp = _mm_mul_ps(r1, r2);
				
				// return _mm_hadd_ps();
				return _mm_cvtss_f32(_mm_dp_ps(r1, r2, 0x71));
			}
		}

		constexpr static vec3 cross(const vec3& u, const vec3& v) {
			if (std::is_constant_evaluated()) {
				// constexpr branch
				return {u.m_e[1] * v.m_e[2] - u.m_e[2] * v.m_e[1],
					u.m_e[2] * v.m_e[0] - u.m_e[0] * v.m_e[2],
					u.m_e[0] * v.m_e[1] - u.m_e[1] * v.m_e[0]};
			} else {
				// runtime branch
				//
				// inspired by:
				// https://geometrian.com/programming/tutorials/cross-product/index.php
				
				__m128 vec0 = _mm_load_ps(u.m_e);
				__m128 vec1 = _mm_load_ps(v.m_e);

				__m128 tmp0 = _mm_shuffle_ps(vec0, vec0, _MM_SHUFFLE(3, 0, 2, 1));
				__m128 tmp1 = _mm_shuffle_ps(vec1, vec1, _MM_SHUFFLE(3, 1, 0, 2));
				__m128 tmp2 = _mm_mul_ps(tmp0, vec1);
				__m128 tmp3 = _mm_mul_ps(tmp0, tmp1);
				__m128 tmp4 = _mm_shuffle_ps(tmp2, tmp2, _MM_SHUFFLE(3, 0, 2, 1));

				return {_mm_sub_ps(tmp3, tmp4)};
			}
		}

		constexpr static vec3 normalize(vec3 v) {
			return v / v.length();
		}

		constexpr float length() const {
			return std::sqrt(length_squared());
		}

		constexpr float length_squared() const {
			if (std::is_constant_evaluated()) {
				// constexpr branch
				return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
			} else {
				// runtime branch
				__m128 r1 = _mm_load_ps(m_e);

				return _mm_cvtss_f32(_mm_dp_ps(r1, r1, 0x71));
			}
		}

		static vec3 randomInUnitSphere() {
			// Generate theta and phi for spherical coordinates, and return
			// the Cartesian coordinates.

			// Spherical to Cartesian conversion: (r, theta, phi) -> (x, y, z)
			// x = r sin theta cos phi
			// y = r sin theta sin phi
			// z = r cos theta

			// Different from the book:
			// https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials
			float thetaRad = randomfloat(0, 1) * std::numbers::pi;
			float phiRad = randomfloat(0, 2) * std::numbers::pi;

			return {sinf(thetaRad) * cosf(phiRad), sinf(thetaRad) * sinf(phiRad), cosf(thetaRad)};
		}

		constexpr bool nearZero() const {
			// Returns true if the vector is close to zero in all dimensions.
			const float threshold = 1e-8;
			return (std::fabs(m_e[0]) < threshold) && (std::fabs(m_e[1]) < threshold) && (std::fabs(m_e[2]) < threshold);
		}

		constexpr static vec3 reflect(const vec3& v, const vec3& normal) {
			return v - 2 * dot(v, normal) * normal;
		}

		constexpr static vec3 refract(
			const vec3& incidentRay, const vec3& normal, float refractiveIndexRatio) {
			float cosTheta = dot(-incidentRay, normal);

			vec3 perpendicularComponent = refractiveIndexRatio * (incidentRay + cosTheta * normal);
			vec3 parallelComponent = -sqrt(1.0 - perpendicularComponent.length_squared()) * normal;

			return perpendicularComponent + parallelComponent;
		}

		static vec3 randomInUnitDisk() {
			while (true) {
				auto p = vec3(randomfloat(-1, 1), randomfloat(-1, 1), 0);
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

	private:
		static float randomfloat(float min, float max) {
			// Returns a random real in [min, max].
			static std::uniform_real_distribution<float> distribution(min, std::nextafter(max, std::numeric_limits<float>::infinity()));
			
			static std::mt19937 generator;

			return distribution(generator);
		}
	
		constexpr vec3(__m128 reg) noexcept {
			_mm_store_ps(m_e, reg);
		}
	
		float m_e[3];
};

// Type aliases for vec3
using point3 = vec3;    // 3D point
