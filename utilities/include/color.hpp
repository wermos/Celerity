#ifndef COLOR_HPP
#define COLOR_HPP

#include <ostream>
#include <random>

class color {
	public:
		constexpr color(
			const float r = 0, const float g = 0, const float b = 0) noexcept
		: m_color{r, g, b} {}

		constexpr float raw_r() const {
			return m_color[0];
		}

		constexpr float raw_g() const {
			return m_color[1];
		}

		constexpr float raw_b() const {
			return m_color[2];
		}

		constexpr int r(float max = 255.0) const {
			return static_cast<int>(max * m_color[0]);
		}

		constexpr int g(float max = 255.0) const {
			return static_cast<int>(max * m_color[1]);
		}

		constexpr int b(float max = 255.0) const {
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

		constexpr color& operator*=(float t) {
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

		friend constexpr color operator*(float t, const color& c) {
			color copy = c;
			copy *= t;
			return copy;
		}

		friend constexpr color operator*(const color& c, float t) {
			color copy = c;
			copy *= t;
			return copy;
		}

		static float randomFloat() {
			// Returns a random real number in [-1, 1].
			static std::uniform_real_distribution<float> distribution(-1, std::nextafter(1, std::numeric_limits<float>::infinity()));

			static std::mt19937 generator;

			return distribution(generator);
		}

		static float randomFloat(float min, float max) {
			// Returns a random real number in [min, max].
			static std::uniform_real_distribution<float> distribution(min, std::nextafter(max, std::numeric_limits<float>::infinity()));
			
			static std::mt19937 generator;

			return distribution(generator);
		}

		static color random() {
			return {randomFloat(), randomFloat(), randomFloat()};
		}

		static color random(float min, float max) {
			return {randomFloat(min, max), randomFloat(min, max), randomFloat(min, max)};
		}

	private:
		float m_color[3];

		constexpr float clamp(float x, float min, float max) {
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
