//
// Created by Cooki on 4/7/2020.
//

#ifndef RAYTRACING_CAMERA_HPP
#define RAYTRACING_CAMERA_HPP

#include "ray.hpp"

class Camera {
	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lensRadius;
public:
	Camera(vec3 lookFrom, vec3 lookAt, vec3 lookUp, float vFov, float aspect, float aperture, float focusDist);
	Ray getRay(float u, float v);
};

#endif //RAYTRACING_CAMERA_HPP
