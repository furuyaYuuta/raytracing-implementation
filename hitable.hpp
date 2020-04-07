//
// Created by Cooki on 4/7/2020.
//

#ifndef RAYTRACING_HITABLE_HPP
#define RAYTRACING_HITABLE_HPP

#include "ray.hpp"

struct hit_record {
	float t{};
	vec3 point;
	vec3 normal;
};

class Hitable {
public:
	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record& record) const = 0;
};

#endif //RAYTRACING_HITABLE_HPP
