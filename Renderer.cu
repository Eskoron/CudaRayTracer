#include "Renderer.h"
kernel void GetSphereIntersectionKernel(const Ray* D_Rays, const Sphere* D_Spheres, const uint spheres, const float Width, const float Height, Color* C){

	const int2 thread_2D_pos = make_int2(blockIdx.x * blockDim.x + threadIdx.x,
		blockIdx.y * blockDim.y + threadIdx.y);

	if (thread_2D_pos.x >= Width || thread_2D_pos.y >= Height){
		return;
	}

	//1D-Position In Image
	const int thread_1D_pos = thread_2D_pos.y * Width + thread_2D_pos.x;
	float Dist = FLT_MAX;
	for (uint i = 0; i < spheres; i++){
		D_Spheres[i].intersectRay(D_Rays[thread_1D_pos], Dist);
	}

	C[thread_1D_pos].A = 255.0f;
	C[thread_1D_pos].B = 255.0f;
	C[thread_1D_pos].G = 255.0f;

	if (Dist < FLT_MAX){
		C[thread_1D_pos].R = 255.0f;
	}


}