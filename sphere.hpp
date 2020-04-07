//
// Created by Cooki on 4/7/2020.
//

#ifndef RAYTRACING_SPHERE_HPP
#define RAYTRACING_SPHERE_HPP

#include "hitable.hpp"

class Sphere : public Hitable {
	vec3 center;
	float radius{};
public:
	Sphere() = default;
	Sphere(const vec3 &center, float radius) : center(center), radius(radius) {}
	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record& record) const;
};

#endif //RAYTRACING_SPHERE_HPP
