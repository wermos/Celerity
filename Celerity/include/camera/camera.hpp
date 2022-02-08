#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"
#include "ray.hpp"

#include "utility.hpp"

#include <cmath>

class Camera {
	public:
		Camera(point3 lookFrom, point3 lookAt, vec3 viewUp,
			   double vfov, double aspectRatio) {
			// vfov = vertical field-of-view, in degrees
			const auto theta = degreesToRadians(vfov);
			const auto h = tan(theta / 2);
			const auto viewportHeight = 2.0 * h;
			const auto viewportWidth = aspectRatio * viewportHeight;

			const auto focalLength = 1.0;

			// Now we have a complete orthonormal basis (u,v,w) to describe
			// our camera’s orientation.
			auto w = unitVector(lookFrom - lookAt);
			auto u = unitVector(cross(viewUp, w));
			auto v = cross(w, u);

			m_origin = lookFrom;
			m_horizontal = viewportWidth * u;
			m_vertical = viewportHeight * v;
			m_lowerLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - w;
		}

		const ray getRay(Float s, Float t) const {
			return {m_origin, m_lowerLeftCorner + (s * m_horizontal) + (t * m_vertical) - m_origin};
		}

	private:
		point3 m_origin;
		point3 m_lowerLeftCorner;
		vec3 m_horizontal;
		vec3 m_vertical;
};

#endif // CAMERA_HPP
