#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <limits>
#include "camera.h"
#include "hitableList.h"
#include "material.h"
#include "sampler.h"
#include "sphere.h"

static vec3 color(const Ray& r, Hitable* world, UniformRandomSampler& sampler, int depth) {
	hitRecord rec;
	if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec)) {
		Ray scattered;
		vec3 attenuation;

		if (depth < 50 && rec.material->scatter(r, rec, sampler, attenuation, scattered)) {
			return gammaCorrect(attenuation, 2.2f) * color(scattered, world, sampler, depth + 1);
		}
		else {
			return vec3(0.0f, 0.0f, 0.0f);
		}
	}
	else {
		vec3 unitDirection = normalize(r.direction());
		float t = 0.5f * (unitDirection.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

static Hitable* munsellColorChart() {
	int rows = 4;
	int columns = 6;
	int sphereCount = (rows * columns) + 1;
	Hitable** list = new Hitable*[sphereCount];
	list[0] = new Sphere(vec3(0.0f, -100.5f, -1.0f), 100, new Lambertian(vec3(0.8f, 0.8f, 0.8f)));

	static vec3 munsellChartColors[24] = {
		vec3(225,222,220), vec3(201,201,201), vec3(172,171,171), vec3(129,132,130), vec3(85,85,85), vec3(53,52,52),
		vec3(26,57,142), vec3(104,152,80), vec3(170,54,69), vec3(232,198,73), vec3(183,94,153), vec3(60,138,176),
		vec3(191,114,59), vec3(69,91,161), vec3(187,91,109), vec3(86,63,101), vec3(175,94,79), vec3(217,158,63),
		vec3(96, 71, 62), vec3(182,146,134), vec3(96,122,157), vec3(94,108,57), vec3(138,136,177), vec3(141,192,181)
	};
	
	float sphereRadius = 0.5f;
	int i = 1;
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < columns; ++x) {
			list[i++] = new Sphere(vec3(x * sphereRadius * 2.0f, y * sphereRadius * 2.0f, 0.0f), sphereRadius, new Lambertian(munsellChartColors[i-1]));
		}
	}

	return new HitableList(list, sphereCount);
}

int main() {
	const int nx = 200;
	const int ny = 100;
	const int ns = 50;

	std::cout << "P3\n" 
			  << nx << " " << ny 
			  << "\n255\n";

	Hitable* world = munsellColorChart();

	UniformRandomSampler sampler;

	vec3 lookFrom(2.5f, 1.5f, 8.0f);
	vec3 lookAt(2.5f, 1.5f, 0.0f);
	const float apeture = 2.0f;
	const float distToFocus = (lookFrom - lookAt).length();
	Camera camera(lookFrom, lookAt, vec3(0.0f, 1.0f, 0.0f), 35, float(nx) / float(ny), apeture, distToFocus);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0.0f, 0.0f, 0.0f);

			for (int s = 0; s < ns; ++s) {
				const float u = float(i + sampler.getNextSample()) / float(nx);
				const float v = float(j + sampler.getNextSample()) / float(ny);
				const Ray r = camera.getRay(u, v, sampler);
				col += color(r, world, sampler, 0);
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

	delete world;
	// need to properly delete everything else.
}
