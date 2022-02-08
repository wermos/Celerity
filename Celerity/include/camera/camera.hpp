#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"
#include "ray.hpp"

#include "utility.hpp"

#include <cmath>

class Camera {
	public:
		Camera(double vfov, double aspectRatio) {
			// vfov = vertical field-of-view, in degrees
			const auto theta = degreesToRadians(vfov);
			const auto h = tan(theta / 2);
			const auto viewportHeight = 2.0 * h;
			const auto viewportWidth = aspectRatio * viewportHeight;

			const auto focalLength = 1.0;

			m_origin = point3(0, 0, 0);
			m_horizontal = vec3(viewportWidth, 0.0, 0.0);
			m_vertical = vec3(0.0, viewportHeight, 0.0);
			m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - vec3(0, 0, focalLength);
		}

		const ray getRay(Float u, Float v) const {
			return {m_origin, m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_origin};
		}

	private:
		point3 m_origin;
		point3 m_lowerLeftCorner;
		vec3 m_horizontal;
		vec3 m_vertical;
};

#endif // CAMERA_HPP
