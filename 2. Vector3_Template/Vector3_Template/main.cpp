#include "Vector3.h"
#include <iostream>

int main() {

	Vector3<float> b(0, 1, 0);
	std::cout << "B: (" << b.x << ", " << b.y << ", " << b.z << ")" << std::endl;
	
	Vector3<float> c(b);
	std::cout << "C: (" << c.x << ", " << c.y << ", " << c.z << ")" << std::endl;

	Vector3<float> d(1, 1, 0);
	d.Scale((float)2);
	
	Vector3<float> e = b + d;
	std::cout << "E: (" << e.x << ", " << e.y << ", " << e.z << ")" << std::endl;
	std::cout << "E magnitude: " << e.Magnitude() << std::endl;


	std::cout << "B-E Distance:" << e.DistanceTo(b) << std::endl;

	e.Normalize();
	std::cout << "E Normalized: (" << e.x << ", " << e.y << ", " << e.z << ")" << std::endl;
	
	return 0;
}