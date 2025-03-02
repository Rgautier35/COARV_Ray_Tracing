#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"

class hitable_list : public hitable {
public:
	hitable_list() {}
	hitable_list(hitable **l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	hitable **list;
	int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	// t_max represents the max t in which a hit is important
	// If there is a hit with t > t_max, this is hidden behind the first hit
	double closest_so_far = t_max;

	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
			// If anything on the list hits, the function will return true
			hit_anything = true;
			// If anything is hit within the range of t, we change the closest and the hit_record.
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	// We return whether we found anything in the list of hitable objects that was hit by the ray
	return hit_anything;
}

#endif // HITABLE_LIST_H