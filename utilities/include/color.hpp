#ifndef COLOR_HPP
#define COLOR_HPP

#include <ostream>
#include <random>

#include "float.hpp"

class color {
	public:
		constexpr color(
			const Float r = 0, const Float g = 0, const Float b = 0) noexcept
		: m_color{r, g, b} {}

		constexpr Float raw_r() const {
			return m_color[0];
		}

		constexpr Float raw_g() const {
			return m_color[1];
		}

		constexpr Float raw_b() const {
			return m_color[2];
		}

		constexpr int r(Float max = 255.0) const {
			return static_cast<int>(max * m_color[0]);
		}

		constexpr int g(Float max = 255.0) const {
			return static_cast<int>(max * m_color[1]);
		}

		constexpr int b(Float max = 255.0) const {
			return static_cast<int>(max * m_color[2]);
		}

		constexpr color& operator+=(const color& c) {
			m_color[0] += c.m_color[0];
			m_color[1] += c.m_color[1];
			m_color[2] += c.m_color[2];
			return *this;
		}

		constexpr color& operator*=(const color& c) {
			m_color[0] *= c.m_color[0];
			m_color[1] *= c.m_color[1];
			m_color[2] *= c.m_color[2];
			return *this;
		}

		constexpr color& operator*=(Float t) {
			m_color[0] *= t;
			m_color[1] *= t;
			m_color[2] *= t;
			return *this;
		}

		color combine(int samplesPerPixel);

		friend std::ostream& operator<<(std::ostream& out, const color& pixelColor);

		friend constexpr color operator+(const color& c1, const color& c2) {
			color copy = c1;
			copy += c2;
			return copy;
		}

		friend constexpr color operator*(const color& c1, const color& c2) {
			color copy = c1;
			copy *= c2;
			return copy;
		}

		friend constexpr color operator*(Float t, const color& c) {
			color copy = c;
			copy *= t;
			return copy;
		}

		friend constexpr color operator*(const color& c, Float t) {
			color copy = c;
			copy *= t;
			return copy;
		}

		static Float randomFloat() {
			// Returns a random real number in [-1, 1].
			static std::uniform_real_distribution<Float> distribution(-1, std::nextafter(1, std::numeric_limits<Float>::infinity()));
#ifdef USE_DOUBLE_AS_FLOAT_TYPE
			static std::mt19937_64 generator;
#else
			static std::mt19937 generator;
#endif

			return distribution(generator);
		}

		static Float randomFloat(Float min, Float max) {
			// Returns a random real number in [min, max].
			static std::uniform_real_distribution<Float> distribution(min, std::nextafter(max, std::numeric_limits<Float>::infinity()));
#ifdef USE_DOUBLE_AS_FLOAT_TYPE
			static std::mt19937_64 generator;
#else
			static std::mt19937 generator;
#endif

			return distribution(generator);
		}

		static color random() {
			return {randomFloat(), randomFloat(), randomFloat()};
		}

		static color random(Float min, Float max) {
			return {randomFloat(min, max), randomFloat(min, max), randomFloat(min, max)};
		}

	private:
		Float m_color[3];

		constexpr Float clamp(Float x, Float min, Float max) {
			if (x < min) {
				return min;
			}
			if (x > max) {
				return max;
			}
			return x;
		}
};

#endif // COLOR_HPP
