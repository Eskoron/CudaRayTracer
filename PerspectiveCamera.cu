#include "PerspectiveCamera.h"


kernel void GetRaysKernel(const Vector3& position, const Rotator& Rotation, const float Width, const float Height, const float AspectRatioScale, const  float Scale, Ray* D_Ray){

	const int2 thread_2D_pos = make_int2(blockIdx.x * blockDim.x + threadIdx.x,
		blockIdx.y * blockDim.y + threadIdx.y);

	if (thread_2D_pos.x >= Width || thread_2D_pos.y >= Height){
		return;
	}

	//1D-Position In Image
	const int thread_1D_pos = thread_2D_pos.y * Width + thread_2D_pos.x;

	float Y = (2 * (thread_2D_pos.x + 0.5) / Width - 1) * AspectRatioScale;
	float Z = (1 - 2 * (threadIdx.y + 0.5) / Height) * Scale;
	float NormalizeValue = sqrtf(1 + Y*Y + Z*Z);

	D_Ray[thread_1D_pos].Direction = Vector3(1.0f / NormalizeValue, Y / NormalizeValue, Z / NormalizeValue);
}



