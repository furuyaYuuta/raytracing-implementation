//
// Created by Cooki on 4/7/2020.
//

#include "camera.hpp"

Camera::Camera() {
	lowerLeftCorner = vec3(-2.0, -1.0, -1.0);
	horizontal = vec3(4.0, 0.0, 0.0);
	vertical = vec3(0.0, 2.0, 0.0);
	origin = vec3(0.0, 0.0, 0.0);
}

Ray Camera::getRay(float u, float v) {
	return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}
