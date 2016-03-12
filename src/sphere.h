#pragma once
#include "hitable.h"

class Material;

class Sphere : public Hitable {
public:
	Sphere()
	: center(0.0f, 0.0f, 0.0f),
	  radius(0.0f),
	  material(nullptr)
	{
	}
	Sphere(vec3 cent, float r, Material* mat) : center(cent), radius(r), material(mat) {};
	virtual ~Sphere();
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;

	vec3 center;
	float radius;
	Material* material;
};
