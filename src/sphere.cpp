#include <cmath>
#include "material.h"
#include "sphere.h"
#include "ray.h"

Sphere::~Sphere() {
	delete material;
}

bool Sphere::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const {
	const vec3 oc = r.origin() - center;
	const float a = dot(r.direction(), r.direction());
	const float b = dot(oc, r.direction());
	const float c = dot(oc, oc) - radius * radius;
	const float discriminant = b * b - a * c;

	if (discriminant > 0.0f) {
		const float sqrDiscriminant = std::sqrt(discriminant);
		float temp = (-b - sqrDiscriminant) / a;
		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.material = material;
			return true;
		}
		temp = (-b + sqrDiscriminant) / a;
		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.material = material;
			return true;
		}
	}

	return false;
}
