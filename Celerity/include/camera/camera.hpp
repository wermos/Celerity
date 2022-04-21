#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"
#include "ray.hpp"

#include "utility.hpp"

#include <cmath>

class Camera {
	public:
		Camera(point3 lookFrom, point3 lookAt, vec3 viewUp,
			   Float vfov, Float aspectRatio, Float aperture,
			   Float focusDistance) {
			// vfov = vertical field-of-view, in degrees
			const auto theta = degreesToRadians(vfov);
			const auto h = tan(theta / 2);
			const auto viewportHeight = 2.0 * h;
			const auto viewportWidth = aspectRatio * viewportHeight;

			const auto focalLength = 1.0;

			// Now we have a complete orthonormal basis (u,v,w) to describe
			// our camera’s orientation.
			w = vec3::unitVector(lookFrom - lookAt);
			u = vec3::unitVector(vec3::cross(viewUp, w));
			v = vec3::cross(w, u);

			m_origin = lookFrom;
			m_horizontal = focusDistance * viewportWidth * u;
			m_vertical = focusDistance * viewportHeight * v;
			m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - (focusDistance * w);

			lensRadius = aperture / 2;
		}

		const ray getRay(Float s, Float t) const {
			vec3 rd = lensRadius * vec3::randomInUnitDisk();
			vec3 offset = u * rd.x() + v * rd.y();

			return {m_origin + offset,
				m_lowerLeftCorner + (s * m_horizontal) + (t * m_vertical) - m_origin - offset};
		}

	private:
		point3 m_origin;
		point3 m_lowerLeftCorner;
		vec3 m_horizontal;
		vec3 m_vertical;
		vec3 u, v, w;
		Float lensRadius;
};

#endif // CAMERA_HPP
