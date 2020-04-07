//
// Created by Cooki on 4/7/2020.
//

#ifndef RAYTRACING_HITABLELIST_HPP
#define RAYTRACING_HITABLELIST_HPP

#include "hitable.hpp"

class HitableList : public Hitable {
	int size;
	Hitable **list;
public:
	HitableList() = default;
	HitableList(Hitable **list, int size) : list(list), size(size) {}
	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const;
};

#endif //RAYTRACING_HITABLELIST_HPP
