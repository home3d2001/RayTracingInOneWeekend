#pragma once
#include "ray.h"
#include "vec3.h"

struct hitRecord {
	float t;
	vec3 p;
	vec3 normal;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};
