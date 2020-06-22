//
// Created by Cooki on 4/8/2020.
//

#include <random>
#include <chrono>
#include "randomUtils.hpp"

float randomFloat(float min, float max) {
//	static random_device rd;
	static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static mt19937 engine(seed);
	static uniform_real_distribution<float> dist(min, max);
	return dist(engine);
}

vec3 randomInUnitSphere() {
	vec3 p;
	do p = vec3(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f));
	while(p.squaredLength() >= 1.0f);
	return p;
}

vec3 randomInUnitDisk() {
	vec3 p;
	do p = vec3(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), 0);
	while(dot(p, p) >= 1.0);
	return p;
}