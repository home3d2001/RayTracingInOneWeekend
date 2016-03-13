#include <cmath>
#include "hitable.h"
#include "material.h"
#include "ray.h"
#include "sampler.h"
#include "vec3.h"

bool Lambertian::scatter(const Ray& ray, const hitRecord& rec, UniformRandomSampler& sampler, vec3& attenuation, Ray& scattered) const {
	const vec3 target = rec.p + rec.normal + randomInUnitSphere(sampler);
	scattered = Ray(rec.p, target - rec.p);
	attenuation = albedo;
	return true;
}

bool Metal::scatter(const Ray& ray, const hitRecord& rec, UniformRandomSampler& sampler, vec3& attenuation, Ray& scattered) const {
	const vec3 reflected = reflect(normalize(ray.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + roughness * randomInUnitSphere(sampler));
	attenuation = albedo;
	return dot(scattered.direction(), rec.normal) > 0.0f;
}

static float schilick(float cosine, float refIdx) {
	float r0 = (1.0f - refIdx) / (1.0f + refIdx);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * std::pow((1.0f - cosine), 5.0f);
}

static bool refract(const vec3& v, const vec3& n, float niOverNt, vec3& refracted) {
	const vec3 uv = normalize(v);
	const vec3 un = normalize(n);
	const float dt = dot(uv, un);
	float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dt * dt);

	if (discriminant > 0.0f) {
		refracted = niOverNt * (uv - un * dt) - un * std::sqrt(discriminant);
		return true;
	}

	return false;
}

bool Dielectric::scatter(const Ray& ray, const hitRecord& rec, UniformRandomSampler& sampler, vec3& attenuation, Ray& scattered) const {
	vec3 outwardNormal;
	const vec3 reflected = reflect(ray.direction(), rec.normal);
	float niOverNt = 0.0f;
	attenuation = vec3(1.0f, 1.0f, 1.0f);
	vec3 refracted;
	if (dot(ray.direction(), rec.normal) > 0) {
		outwardNormal = -rec.normal;
		niOverNt = refractiveIndex;
	}
	else {
		outwardNormal = rec.normal;
		niOverNt = 1.0f / refractiveIndex;
	}

	if (refract(ray.direction(), outwardNormal, niOverNt, refracted)) {
		scattered = Ray(rec.p, refracted);
	}
	else {
		scattered = Ray(rec.p, reflected);
		return false;
	}
	return true;
}
