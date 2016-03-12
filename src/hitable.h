#pragma once
#include "vec3.h"

class Ray;
class Material;

struct hitRecord {
	float t;
	vec3 p;
	vec3 normal;
	Material* material;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};
