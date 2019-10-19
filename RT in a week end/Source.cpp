// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <fstream>
#include <iostream>
int main()
{
	std::ofstream myfile;
	myfile.open("spheres.ppm");
	//myfile << "Writing this to a \nfile.\n";
	


	int nx = 400;
	int ny = 200;

	myfile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny-1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			myfile << ir << " " << ig << " " << ib << "\n";
		}
	}






	myfile.close();

}