//
// Created by Cooki on 4/7/2020.
//

#include "camera.hpp"

Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 lookUp, float vFov, float aspect) {
	// vFov is top to bottom in degrees, aspect is the proportion of width and height
	vec3 u, v, w;
	auto theta = static_cast<float>(vFov * M_PI / 180.0);
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	origin = lookFrom;
	w = unit_vector(lookFrom - lookAt);
	u = unit_vector(cross(lookUp, w));
	v = cross(w, u);
	lowerLeftCorner = vec3(-half_width, -half_height, -1.0f);
	lowerLeftCorner = origin - (half_width*u + half_height*v + w);
	horizontal = 2 * half_width * u;
	vertical = 2 * half_height * v;
}

Ray Camera::getRay(float u, float v) {
	return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}
