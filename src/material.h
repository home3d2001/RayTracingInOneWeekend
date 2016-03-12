#pragma once
#include "vec3.h"

class Ray;
struct hitRecord;
struct UniformRandomSampler;

class Material {
public:
	virtual bool scatter(const Ray& ray, const hitRecord& rec, UniformRandomSampler& sampler, vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
	Lambertian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const Ray& ray, const hitRecord& rec, UniformRandomSampler& sampler, vec3& attenuation, Ray& scattered) const override;

	vec3 albedo;
};

class Metal : public Material {
public:
	Metal(const vec3& a, float r) : albedo(a), roughness(r) {
		if (r < 1.0f) {
			roughness = r;
		}
		else {
			roughness = 1.0f;
		}
	}
	virtual bool scatter(const Ray& ray, const hitRecord& rec, UniformRandomSampler& sampler, vec3& attenuation, Ray& scattered) const override;

	vec3 albedo;
	// adhoc rougness
	float roughness;
};

