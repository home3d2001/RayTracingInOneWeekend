#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "ray.h"
#include "sampler.h"

class Camera {
public:
	Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float apeture, float focusDist) 
		: origin(lookfrom),
		  lowerLeftCorner(0.0f, 0.0f, 0.0f),
		  horizontal(0.0f, 0.0f, 0.0f),
		  vertical(0.0f, 0.0f, 0.0f),
		  u(1.0f, 0.0f, 0.0f),
		  v(0.0f, 1.0f, 0.0f),
		  w(0.0f, 0.0f, 1.0f),
		  lensRadius(apeture / 2.0f)
	{
		const float theta = vfov * (float)M_PI / 180.0f;
		const float halfHeight = std::tan(theta / 2.0f);
		const float halfWidth = aspect * halfHeight;

		vec3 w = normalize(lookfrom - lookat);
		vec3 u = normalize(cross(vup, w));
		vec3 v = cross(w, u);

		lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
		horizontal = 2.0f * halfWidth * focusDist * u;
		vertical = 2.0f * halfHeight * focusDist * v;
	}

	Ray getRay(float s, float t, UniformRandomSampler& sampler) {
		vec3 rd = lensRadius * randomInUnitDisk(sampler);
		vec3 offset = u * rd.x() + v * rd.y();
		return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lensRadius;
};
