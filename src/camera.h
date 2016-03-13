#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "ray.h"

class Camera {
public:
	Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) 
		: origin(lookfrom),
		  lowerLeftCorner(0.0f, 0.0f, 0.0f),
		  horizontal(0.0f, 0.0f, 0.0f),
		  vertical(0.0f, 0.0f, 0.0f)
	{
		const float theta = vfov * (float)M_PI / 180.0f;
		const float halfHeight = std::tan(theta / 2.0f);
		const float halfWidth = aspect * halfHeight;

		vec3 w = normalize(lookfrom - lookat);
		vec3 u = normalize(cross(vup, w));
		vec3 v = cross(w, u);

		lowerLeftCorner = vec3(-halfWidth, -halfHeight, -1.0);
		lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
		horizontal = 2.0f * halfWidth * u;
		vertical = 2.0f * halfHeight * v;
	}

	Ray getRay(float u, float v) {
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};
