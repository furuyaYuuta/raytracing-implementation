//
// Created by Cooki on 11/1/2019.
//

#include "vec3.hpp"

vec3 &vec3::operator+=(const vec3 &v2) {
	for(int i = 0; i < 3; i++)
		e[i] += v2.e[i];
	return *this;
}

vec3 &vec3::operator-=(const vec3 &v2) {
	for(int i = 0; i < 3; i++)
		e[i] -= v2.e[i];
	return *this;
}

vec3 &vec3::operator*=(const vec3 &v2) {
	for(int i = 0; i < 3; i++)
		e[i] *= v2.e[i];
	return *this;
}

vec3 &vec3::operator/=(const vec3 &v2) {
	for(int i = 0; i < 3; i++)
		e[i] /= v2.e[i];
	return *this;
}

vec3 &vec3::operator*=(const float& t) {
	for(auto& i : e)
		i *= t;
	return *this;
}

vec3 &vec3::operator/=(const float& t) {
	for(auto& i : e)
		i /= t;
	return *this;
}

istream &operator>>(istream &in, vec3 &t) {
	return in >> t[0] >> t[1] >> t[2];
}

ostream &operator<<(ostream &out, const vec3 &t) {
	return out << t[0] << " " << t[1] << " " << t[2];
}

void vec3::make_unit_vector() {
	float t = 1 / this->length();
	for(auto i : e)
		i *= t;
}

vec3 operator+(const vec3 &v1, const vec3 &v2) {
	return vec3{v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]};
}

vec3 operator-(const vec3 &v1, const vec3 &v2) {
	return vec3{v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]};
}

vec3 operator*(const vec3 &v1, const vec3 &v2) {
	return vec3{v1[0]*v2[0], v1[1]*v2[1], v1[2]*v2[2]};
}

vec3 operator/(const vec3 &v1, const vec3 &v2) {
	return vec3{v1[0]/v2[0], v1[1]/v2[1], v1[2]/v2[2]};
}

vec3 operator*(const vec3 &v1, const float &t) {
	return vec3{v1[0]*t, v1[1]*t, v1[2]*t};
}

vec3 operator/(const vec3 &v1, const float &t) {
	return vec3{v1[0]/t, v1[1]/t, v1[2]/t};
}

vec3 sqrt(const vec3 &v1) {
	return vec3{sqrt(v1[0]), sqrt(v1[1]), sqrt(v1[2])};
}

vec3 unit_vector(const vec3 &v) {
	return v / v.length();
}

float dot(const vec3 &v1, const vec3 &v2) {
	return v1[0]*v2[0] + v1[1]*v2[1] +v1[2]*v2[2];
}

vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3{
		v1[1]*v2[2] - v1[2]*v2[1],
		v1[2]*v2[0] - v1[0]*v2[2],
		v1[0]*v2[1] - v1[1]*v2[0]
	};
}

vec3 reflect(const vec3 &v, const vec3 &n) {
	return v - 2*dot(v, n) * n;
}

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted) {
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if(discriminant > 0) {
		refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
		return true;
	}
	return false;
}
