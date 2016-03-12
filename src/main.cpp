#include <iostream>
#include "vec3.h"

int main() {
	const int nx = 200;
	const int ny = 100;

	std::cout << "P3\n" 
			  << nx << " " << ny 
			  << "\n255\n";

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2f);
			const int ir = int(255.99 * col.r());
			const int ig = int(255.99 * col.g());
			const int ib = int(255.99 * col.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
