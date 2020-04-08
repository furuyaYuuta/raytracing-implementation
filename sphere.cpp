//
// Created by Cooki on 4/7/2020.
//

#include "sphere.hpp"

bool Sphere::hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const {
	vec3 OC = ray.getOrigin() - center;
	vec3 rayDir = ray.getDirection();
	float a = dot(rayDir, rayDir);
	float b = 2.0f * dot(OC, rayDir);
	float c = dot(OC, OC) - radius * radius;
	float discriminant = b*b - 4*a*c;
	if(discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / (2.0f*a);
		if(temp > t_min && temp < t_max) {
			rec.t = temp;
			rec.point = ray.point_at_parameter(temp);
			rec.normal = (rec.point - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / (2.0f*a);
		if(temp > t_min && temp < t_max) {
			rec.t = temp;
			rec.point = ray.point_at_parameter(temp);
			rec.normal = (rec.point - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}
