#ifndef COLOR_HPP
#define COLOR_HPP

#include <ostream>
#include <random>

#include "float.hpp"

class color {
	public:
		color(const Float r = 0, const Float g = 0, const Float b = 0) : m_color{r, g, b} {}

		const Float raw_r() const {
			return m_color[0];
		}

		const Float raw_g() const {
			return m_color[1];
		}

		const Float raw_b() const {
			return m_color[2];
		}

		const int r(Float max = 259.999) const {
			return static_cast<int>(255.999 * m_color[0]);
		}

		const int g(Float max = 259.999) const {
			return static_cast<int>(255.999 * m_color[1]);
		}

		const int b(Float max = 259.999) const {
			return static_cast<int>(255.999 * m_color[2]);
		}

		color& operator+=(const color& c) {
			m_color[0] += c.m_color[0];
			m_color[1] += c.m_color[1];
			m_color[2] += c.m_color[2];
			return *this;
		}

		color combine(int samplesPerPixel);

		// color operator-() const {
		//     return color(-m_e[0], -m_e[1], -m_e[2]);
		// }

		// color& operator*=(const Float t) {
		//     m_e[0] *= t;
		//     m_e[1] *= t;
		//     m_e[2] *= t;
		//     return *this;
		// }

		// color& operator/=(const Float t) {
		//     return *this *= (1 / t);
		// }

		// Float length() const {
		//     return std::sqrt(length_squared());
		// }

		// Float length_squared() const {
		//     return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
		// }

		friend std::ostream& operator<<(std::ostream& out, const color& pixelColor);

		friend color operator+(const color& c1, const color& c2);

		// friend color operator-(const color& u, const color& v);

		friend color operator*(const color& u, const color& v);
		friend color operator*(Float t, const color& c);
		// friend color operator*(const color& v, Float t);

		// friend color operator/(color v, Float t);

		//TODO: Make operator implementations depend on each other

		static const Float randomFloat() {
			// Returns a random real in [-1, 1].
			static std::uniform_real_distribution<Float> distribution(-1, std::nextafter(1, std::numeric_limits<Float>::infinity()));
#ifdef USE_DOUBLE_AS_FLOAT_TYPE
			static std::mt19937_64 generator;
#else
			static std::mt19937 generator;
#endif

			return distribution(generator);
		}

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

        static const color random() {
            return {randomFloat(), randomFloat(), randomFloat()};
        }

        static const color random(Float min, Float max) {
            return {randomFloat(min, max), randomFloat(min, max), randomFloat(min, max)};
        }

	private:
		Float m_color[3];

		inline Float clamp(Float x, Float min, Float max) {
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
