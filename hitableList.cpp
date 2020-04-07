//
// Created by Cooki on 4/7/2020.
//

#include "hitableList.hpp"

bool HitableList::hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for(int i = 0; i < size; i++) {
		if(list[i]->hit(ray, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}
