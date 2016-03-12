#pragma once
#include "hitable.h"

class Sphere : public Hitable {
public:
	Sphere() {}
	Sphere(vec3 cent, float r) : center(cent), radius(r) {};
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;

	vec3 center;
	float radius;
};
