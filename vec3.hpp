//
// Created by Cooki on 11/1/2019.
//

#ifndef RAYTRACING_VEC3_HPP
#define RAYTRACING_VEC3_HPP

#include <iostream>
#include <cmath>

using namespace std;

class vec3 {
private:
	float e[3]={};
public:
	vec3() = default;
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

	inline float x() { return e[0]; }
	inline float y() { return e[1]; }
	inline float z() { return e[2]; }
	inline float r() { return e[0]; }
	inline float g() { return e[1]; }
	inline float b() { return e[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3{-e[0], -e[1], -e[2]}; }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v2);
	vec3& operator-=(const vec3& v2);
	vec3& operator*=(const vec3& v2);
	vec3& operator/=(const vec3& v2);
	vec3& operator*=(const float& t);
	vec3& operator/=(const float& t);

	[[nodiscard]] inline float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
	[[nodiscard]] inline float squaredLength() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
	inline void make_unit_vector();

	friend istream& operator>>(istream &in, vec3 &t);
	friend ostream& operator<<(ostream &out, const vec3 &t);
	friend vec3 operator+(const vec3 &v1, const vec3 &v2);
	friend vec3 operator-(const vec3 &v1, const vec3 &v2);
	friend vec3 operator*(const vec3 &v1, const vec3 &v2);
	friend vec3 operator/(const vec3 &v1, const vec3 &v2);
	friend vec3 operator*(const vec3 &v1, const float &t);
	friend vec3 operator/(const vec3 &v1, const float &t);
	friend vec3 operator*(const float &t, const vec3 &v1) { return v1 * t; }
	friend vec3 sqrt(const vec3 &v1);
};

float dot(const vec3 &v1, const vec3 &v2);
vec3 cross(const vec3 &v1, const vec3 &v2);
vec3 unit_vector(const vec3 &v1);
vec3 reflect(const vec3 &v, const vec3 &n);
bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted);

#endif //RAYTRACING_VEC3_HPP