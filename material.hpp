//
// Created by Cooki on 4/8/2020.
//

#ifndef RAYTRACING_MATERIAL_HPP
#define RAYTRACING_MATERIAL_HPP

#include "ray.hpp"
#include "hitable.hpp"

class Material {
public:
	virtual bool scatter(const Ray& rayIn, const hit_record& record, vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
	vec3 albedo;
public:
	explicit Lambertian(const vec3& albedo) : albedo(albedo) {}
	bool scatter(const Ray& rayIn, const hit_record& record, vec3& attenuation, Ray& scattered) const override;
};

class Metal : public Material {
	vec3 albedo;
	float fuzz;
public:
	Metal(const vec3& albedo, float fuzzy) : albedo(albedo), fuzz(fuzz) {}
	bool scatter(const Ray& rayIn, const hit_record& record, vec3& attenuation, Ray& scattered) const override;
};

float schlick(float cosine, float ref_idx);

class Dielectric : public Material {
	float ref_idx;
public:
	explicit Dielectric(float ref_idx) : ref_idx(ref_idx) {}
	bool scatter(const Ray& rayIn, const hit_record& record, vec3& attenuation, Ray& scattered) const override;
};

#endif //RAYTRACING_MATERIAL_HPP
