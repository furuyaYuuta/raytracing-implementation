//
// Created by Cooki on 4/8/2020.
//

#include "material.hpp"

#include <random>

float randomFloat(float min, float max) {
	static random_device rd;
	static  mt19937 e2(rd());
	uniform_real_distribution<float> dist(min, max);
	return dist(e2);
}

vec3 randomInUnitSphere() {
	vec3 p;
	do p = 2.0 * vec3(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f));
	while(p.squaredLength() >= 1.0f);
	return p;
}

bool Lambertian::scatter(const Ray &rayIn, const hit_record &record, vec3 &attenuation, Ray &scattered) const {
	vec3 target = record.point + record.normal + randomInUnitSphere();
	scattered = Ray(record.point, target - record.point);
	attenuation = albedo;
	return true;
}

bool Metal::scatter(const Ray &rayIn, const hit_record &record, vec3 &attenuation, Ray &scattered) const {
	vec3 reflected = reflect(unit_vector(rayIn.getDirection()), record.normal);
	scattered = Ray(record.point, reflected);
	attenuation = albedo;
	// if the angle of two vectors is within 90 degrees
	return dot(scattered.getDirection(), record.normal) > 0;
}

bool Dielectric::scatter(const Ray &rayIn, const hit_record &record, vec3 &attenuation, Ray &scattered) const {
	vec3 outwardNormal;
	vec3 reflected = reflect(unit_vector(rayIn.getDirection()), record.normal);
	float ni_over_nt;
	// the glass surface absorb nothing
	attenuation = vec3(1.0f, 1.0f, 1.0f);
	vec3 refracted;
	if(dot(rayIn.getDirection(), record.normal) > 0 ) {
		// when the angle of two vectors is within 90 degrees
		outwardNormal = -record.normal;
		ni_over_nt = ref_idx;
	} else {
		// when the angle of two vectors is more than 90 degrees
		// possible situation is that the ray goes through the object and hit the opposite surface
		outwardNormal = record.normal;
		ni_over_nt = 1.0f / ref_idx;
	}

	if(refract(rayIn.getDirection(), outwardNormal, ni_over_nt, refracted)) {
		scattered = Ray(record.point, refracted);
		return true;
	}
	else {
		scattered = Ray(record.point, reflected);
		return false;
	}
}
