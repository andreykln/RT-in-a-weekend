// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <fstream>
#include <iostream>
#include "vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "hitablelist.h"
#include "sphere.h"

vec3 color(const ray& r, hitable* world);
//float hit_sphere(const vec3& center, float radius, const ray& r);


int main()
{
	std::ofstream myfile;
	myfile.open("spheres.ppm");
	int nx = 400;
	int ny = 200;
	myfile << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	hitable *list[3];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	list[2] = new sphere(vec3(1, -0.5, -1), 0.3);
	hitable* world = new hitable_list(list, 3);
	unsigned int iterations{};

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 p = r.point_at_parameter(2.0);
			vec3 col = color(r,world);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			myfile << ir << " " << ig << " " << ib << "\n";
			iterations++;
		}
	}
	myfile.close();
	std::cout << iterations;
}

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec))
	{
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}

	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1.0);
	}

}

/*float hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = (dot(oc, oc)) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (double(-b) - std::sqrt(discriminant)) / (2.0*a) ;
	}
}*/

