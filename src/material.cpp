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
	const vec3 reflected = reflect(makeUnitVector(ray.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + roughness * randomInUnitSphere(sampler));
	attenuation = albedo;
	return dot(scattered.direction(), rec.normal) > 0.0f;
}
