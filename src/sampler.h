#pragma once
#include <random>
#include "vec3.h"

struct UniformRandomSampler {
	UniformRandomSampler()
		: gen(std::random_device()())
	{
	}

	float getNextSample() {
		std::uniform_real_distribution<float> dis(0.0f, 1.0f);
		return (float)dis(gen);
	}

	std::mt19937 gen;
};

vec3 randomInUnitSphere(UniformRandomSampler& sampler);
vec3 randomInUnitDisk(UniformRandomSampler& sampler);
