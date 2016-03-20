#include "cuda_runtime.h"
#include "curand_kernel.h"
#include "cutil_math.h"
#include "device_launch_parameters.h"

#include <assert.h>
#include <stdio.h>

#include <GLFW/glfw3.h>

#define M_PI 3.14159265359f

struct Ray { 
	float3 o;
	float3 d;
	__device__ Ray(float3 a, float3 b) : o(a), d(b) {} 
};

__device__ float3 color(Ray& r) {
	float3 unitDirection = normalize(r.d);
	float t = 0.5f * (unitDirection.y + 1.0f);
	float3 white = make_float3(1.0f, 1.0f, 1.0f);
	float3 blue = make_float3(0.5f, 0.7f, 1.0f);
	return (1.0f - t) * white + t * blue;
}

__global__ void render(float3* pixels, const unsigned int sizeX, const unsigned int sizeY) {
	 unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;   
	 unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;

	 unsigned int idx = y * sizeX + x;

	 curandState randState;
	 curand_init(idx, 0, 0, &randState);

	 float3 lowerLeftCorner = make_float3(-2.0f, -1.0f, -1.0f);
	 float3 horizontal = make_float3(4.0f, 0.0f, 0.0f);
	 float3 vertical = make_float3(0.0f, 2.0f, 0.0f);
	 float3 origin = make_float3(0.0f, 0.0f, 0.0f);

	 float u = x / (float)sizeX;
	 float v = 1 - y / (float)sizeY;

	 Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);

	 pixels[idx] = color(r);
}

__global__ void clearPixels(float3* pixels, const unsigned int sizeX, const unsigned int sizeY) {
	 unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;   
	 unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;
	 pixels[y * sizeX + x] = make_float3(103 / 255.0f, 189 / 255.0f, 170 / 255.0f);
}

__global__ void randomPixels(float3* pixels, const unsigned int sizeX, const unsigned int sizeY) {
	 unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;   
	 unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;

	 unsigned int idx = y * sizeX + x;

	 curandState randState;
	 curand_init(idx, 0, 0, &randState);

	 pixels[idx] = make_float3(curand_uniform(&randState), curand_uniform(&randState), curand_uniform(&randState));
}

#define VERIFY_CUDA(x) \
{ \
	cudaError_t cudaStatus = (x); \
	if (cudaStatus != cudaSuccess) { \
		fprintf(stderr, "CUDA Call Failed."); \
		assert(0); \
	} \
} \

cudaError_t clearImageWithCuda(float3 color, float3* hostPixels, unsigned int sizeX, unsigned int sizeY) {
	VERIFY_CUDA(cudaSetDevice(0));

	size_t byteCount = sizeX * sizeY * sizeof(float3);

	float3* devicePixels = nullptr;
	VERIFY_CUDA(cudaMalloc((void**)&devicePixels, byteCount));
	VERIFY_CUDA(cudaMemcpy(devicePixels, hostPixels, byteCount, cudaMemcpyHostToDevice));

	dim3 block(16, 16, 1);
	dim3 grid(sizeX / block.x, sizeY / block.y, 1);
	render<<<grid, block>>>(devicePixels, sizeX, sizeY);
	VERIFY_CUDA(cudaGetLastError());
	VERIFY_CUDA(cudaDeviceSynchronize());
	VERIFY_CUDA(cudaMemcpy(hostPixels, devicePixels, byteCount, cudaMemcpyDeviceToHost));

	VERIFY_CUDA(cudaFree(devicePixels));

	return cudaSuccess;
}

int main()
{
	const int nx = 1280;
	const int ny = 720;

    if (!glfwInit())
        return -1;

	float3* pixels = new float3[nx * ny];

	cudaError_t cudaStatus = clearImageWithCuda(make_float3(1.0f, 0.0f, 1.0f), pixels, nx, ny);
	if (cudaStatus != cudaSuccess) {
	    fprintf(stderr, "clearImageWithCuda failed!");
        return 1;
	}

	FILE* f = fopen( "gpu.ppm", "w" );
	fprintf(f, "P3\n%d %d\n%d\n", nx, ny, 255);
	for (int i = 0; i < nx * ny; ++i) {
		fprintf(f, "%d %d %d ", int(255.99 * pixels[i].x),
								int(255.99 * pixels[i].y),
								int(255.99 * pixels[i].z));
	}
	fclose(f);
	delete[] pixels;

    VERIFY_CUDA(cudaDeviceReset());

    return 0;
}
