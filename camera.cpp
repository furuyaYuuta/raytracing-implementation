//
// Created by Cooki on 4/7/2020.
//

#include "camera.hpp"
#include "randomUtils.hpp"

Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 lookUp, float vFov, float aspect, float aperture, float focusDist) {
	// vFov is top to bottom in degrees, aspect is the proportion of width and height
	lensRadius = aperture / 2.0f;
	auto theta = static_cast<float>(vFov * M_PI / 180.0);
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	origin = lookFrom;
	w = unit_vector(lookFrom - lookAt);
	u = unit_vector(cross(lookUp, w));
	v = cross(w, u);
	lowerLeftCorner = origin - focusDist * (half_width*u + half_height*v + w);
	horizontal = 2 * half_width * focusDist * u;
	vertical = 2 * half_height * focusDist * v;
}

Ray Camera::getRay(float s, float t) {
	vec3 rd = lensRadius * randomInUnitDisk();
	vec3 offset = u * rd.x() + v * rd.y();
	return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
}
