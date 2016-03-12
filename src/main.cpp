#include <iostream>
#include <limits>
#include <random>
#include "camera.h"
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
	const int nx = 200;
	const int ny = 100;
	const int ns = 100;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0f, 1.0f);

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

	Camera camera;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0.0f, 0.0f, 0.0f);

			for (int s = 0; s < ns; ++s) {
				const float u = float(i + dis(gen)) / float(nx);
				const float v = float(j + dis(gen)) / float(ny);
				const Ray r = camera.getRay(u, v);
				col += color(r, world);
			}

			col /= float(ns);

			const int ir = int(255.99 * col.r());
			const int ig = int(255.99 * col.g());
			const int ib = int(255.99 * col.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
