//
// Created by Cooki on 4/7/2020.
//

#ifndef RAYTRACING_SPHERE_HPP
#define RAYTRACING_SPHERE_HPP

#include "hitable.hpp"
#include "material.hpp"

class Sphere : public Hitable {
	vec3 center;
	float radius{};
	Material *mat_ptr{};

public:
	Sphere() = default;
	Sphere(const vec3 &center, float radius, Material *mat_ptr) : center(center), radius(radius), mat_ptr(mat_ptr) {}
	bool hit(const Ray& ray, float t_min, float t_max, hit_record& record) const override;
};

#endif //RAYTRACING_SPHERE_HPP
