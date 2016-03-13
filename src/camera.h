#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "ray.h"

class Camera {
public:
	Camera(float vfov, float aspect) 
		: origin(0.0f, 0.0f, 0.0f),
		  lowerLeftCorner(0.0f, 0.0f, 0.0f),
		  horizontal(0.0f, 0.0f, 0.0f),
		  vertical(0.0f, 0.0f, 0.0f)
	{
		const float theta = vfov * (float)M_PI / 180.0f;
		const float halfHeight = std::tan(theta / 2.0f);
		const float halfWidth = aspect * halfHeight;
		lowerLeftCorner = vec3(-halfWidth, -halfHeight, -1.0);
		horizontal = vec3(2.0f * halfWidth, 0.0f, 0.0f);
		vertical = vec3(0.0f, 2.0f * halfHeight, 0.0);
	}

	Ray getRay(float u, float v) {
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};
