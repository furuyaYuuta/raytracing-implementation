//
// Created by Cooki on 4/7/2020.
//

#ifndef RAYTRACING_RAY_HPP
#define RAYTRACING_RAY_HPP

#include "vec3.hpp"

class Ray {
	vec3 origin;
	vec3 direction;
public:
	Ray() = default;
	Ray(const vec3& origin, const vec3& direction) : origin(origin), direction(direction) {}
	[[nodiscard]] inline vec3 getOrigin() const { return origin; }
	[[nodiscard]] inline vec3 getDirection() const { return direction; }
	[[nodiscard]] inline vec3 point_at_parameter(float t) const { return origin + t * direction; }
};

#endif //RAYTRACING_RAY_HPP
