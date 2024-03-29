#pragma once

#include "vec3.hpp"

class ray {
	public:
		constexpr ray() noexcept {}
		constexpr ray(const point3& origin, const vec3& direction) noexcept
			: m_origin(origin), m_direction(direction) {}

		constexpr point3 origin() const {
			return m_origin;
		}

		constexpr vec3 direction() const {
			return m_direction;
		}

		constexpr point3 at(float t) const {
			return m_origin + t * m_direction;
		}

	private:
		point3 m_origin;
		vec3 m_direction;
};
