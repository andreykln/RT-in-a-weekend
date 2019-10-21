#ifndef HITABLELIST_H
#define  HITABLELIST_H
#include "Hitable.h"
//#include <iostream>

class hitable_list : public hitable
{
public:
	hitable** list{};
	int list_size{};
	hitable_list() {};
	hitable_list(hitable** l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;

};
 

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	//std::cout << "Hit in hitable list has been called\n";
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (ptrdiff_t i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}





#endif // HITABLELIST_H
