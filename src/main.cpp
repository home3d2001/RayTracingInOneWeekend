#include <iostream>
#include <limits>
#include "sphere.h"
#include "hitableList.h"

vec3 color(const Ray& r, Hitable* world) {
	hitRecord rec;
	if (world->hit(r, 0.0f, std::numeric_limits<float>::max(), rec)) {
		return 0.5f * (rec.normal + vec3(1.0f, 1.0f, 1.0f));
	}
	else {
		vec3 unitDirection = makeUnitVector(r.direction());
		float t = 0.5f * (unitDirection.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main() {
	const int nx = 1200;
	const int ny = 600;

	std::cout << "P3\n" 
			  << nx << " " << ny 
			  << "\n255\n";

	const vec3 lowerLeftCorner(-2.0f, -1.0f, -1.0f);
	const vec3 horizontal(4.0f, 0.0f, 0.0f);
	const vec3 vertical(0.0f, 2.0f, 0.0f);
	const vec3 origin(0.0f, 0.0f, 0.0f);

	Hitable* list[2] = { nullptr };
	list[0] = new Sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
	list[1] = new Sphere(vec3(0.0f, -100.5f, -1.0f), 100);

	Hitable* world = new HitableList(list, 2);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			const float u = float(i) / float(nx);
			const float v = float(j) / float(ny);
			const Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);
			const vec3 col = color(r, world);
			const int ir = int(255.99 * col.r());
			const int ig = int(255.99 * col.g());
			const int ib = int(255.99 * col.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
