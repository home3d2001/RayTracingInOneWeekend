#pragma once
#include "ray.h"

class Camera {
public:
	Camera() 
		: origin(0.0f, 0.0f, 0.0f),
		  lowerLeftCorner(-2.0f, -1.0f, -1.0f),
		  horizontal(4.0f, 0.0f, 0.0f),
		  vertical(0.0f, 2.0f, 0.0f)
	{

	}

	Ray getRay(float u, float v) {
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};
