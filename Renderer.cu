#include "Renderer.h"



kernel void GetSphereIntersectionKernel(const Ray* D_Rays, const Sphere* D_Spheres, const uint spheres, const uint Width, const uint Height, Color* Device_Color){

	const int2 thread_2D_pos = make_int2(blockIdx.x * blockDim.x + threadIdx.x,
		blockIdx.y * blockDim.y + threadIdx.y);

	if (thread_2D_pos.x >= Width || thread_2D_pos.y >= Height){
		return;
	}

	//1D-Position In Image
	const int thread_1D_pos = thread_2D_pos.y * Width + thread_2D_pos.x;
	//float Dist = FLT_MAX;
	//for (uint i = 0; i < spheres; i++){
		//D_Spheres[i].intersectRay(D_Rays[thread_1D_pos], Dist);
	//}

	Device_Color[thread_1D_pos].A = 0xFF;
	Device_Color[thread_1D_pos].B = 0x00;
	Device_Color[thread_1D_pos].G = 0xFF;
	Device_Color[thread_1D_pos].R = 0x00;
	//if (Dist < FLT_MAX){
		//Device_Color[thread_1D_pos].G = 0x00;
	//}


}