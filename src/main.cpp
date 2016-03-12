#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include "camera.h"
#include "sphere.h"
#include "hitableList.h"

struct UniformRandomSampler {
	UniformRandomSampler()
		: gen(std::random_device()())
	{
	}

	float getNextSample() {
		std::uniform_real_distribution<float> dis(0.0f, 1.0f);
		return (float)dis(gen);
	}

	std::mt19937 gen;
};

// easiest algorithm: rejection method
vec3 randomInUnitSphere(UniformRandomSampler& sampler) {
	vec3 p;
	do {
		p = 2.0f * vec3(sampler.getNextSample(), sampler.getNextSample(), sampler.getNextSample()) - vec3(1.0f, 1.0f, 1.0f);
	} while (dot(p, p) >= 1.0);
	return p;
}

vec3 color(const Ray& r, Hitable* world, UniformRandomSampler& sampler) {
	hitRecord rec;
	if (world->hit(r, 0.0f, std::numeric_limits<float>::max(), rec)) {
		const vec3 target = rec.p + rec.normal + randomInUnitSphere(sampler);
		return 0.5f * color(Ray(rec.p, target - rec.p), world, sampler); // (rec.normal + vec3(1.0f, 1.0f, 1.0f));
	}
	else {
		vec3 unitDirection = makeUnitVector(r.direction());
		float t = 0.5f * (unitDirection.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main() {
	const int nx = 600;
	const int ny = 300;
	const int ns = 100;

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

	UniformRandomSampler sampler;

	Camera camera;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0.0f, 0.0f, 0.0f);

			for (int s = 0; s < ns; ++s) {
				const float u = float(i + sampler.getNextSample()) / float(nx);
				const float v = float(j + sampler.getNextSample()) / float(ny);
				const Ray r = camera.getRay(u, v);
				col += color(r, world, sampler);
			}

			col /= float(ns);

			constexpr float gamma = 1.0f / 2.2f;
			col = vec3(std::pow(col.r(), gamma), std::pow(col.g(), gamma), std::pow(col.b(), gamma));

			const int ir = int(255.99 * col.r());
			const int ig = int(255.99 * col.g());
			const int ib = int(255.99 * col.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
