#include "sampler.h"

// easiest algorithm: rejection method
vec3 randomInUnitSphere(UniformRandomSampler& sampler) {
	vec3 p;
	do {
		p = 2.0f * vec3(sampler.getNextSample(), sampler.getNextSample(), sampler.getNextSample()) - vec3(1.0f, 1.0f, 1.0f);
	} while (dot(p, p) >= 1.0);
	return p;
}
