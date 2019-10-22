#ifndef MATERIAL_H
#define MATERIAL_H
#include "Hitable.h"
#include "hitablelist.h"
#include "random_double.h"

struct hit_record;
vec3 random_in_unit_sphere();
vec3 reflect(const vec3& v, const vec3& n);


class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material 
{
public:
	vec3 albedo;

	lambertian(const vec3& a) : albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};

class metal : public material
{
public:
	vec3 albedo;

	metal (const vec3& a) : albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0 * vec3(random_double(), random_double(), random_double()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

#endif
