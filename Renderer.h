#pragma once
#include "CudaDefines.h"
#include "Ray.h"
#include "Sphere.h"
#include "Image.h"
#include "PerspectiveCamera.h"
struct Renderer{

	uint Width = 400;
	uint Height = 400;

	forceinline Renderer(uint InWidth, uint InHeight):Width(InWidth),Height(InHeight){

	}

	forceinline void Render(const PerspectiveCamera* Camera,  const Sphere* H_Spheres, const uint Sphere_Amount,Color* H_Colors) const;



};

kernel void GetSphereIntersectionKernel(const Ray* D_Rays, const Sphere* D_Spheres, const uint spheres, const uint Width, const uint Height, Color* c);


forceinline void Renderer::Render(const PerspectiveCamera* Camera, const Sphere* H_Spheres, const uint Sphere_Amount, Color* H_Colors) const{

	Ray* D_Rays;
	cudaMalloc((void**)&D_Rays, Width * Height * sizeof(Ray));
	Camera->GetRays(D_Rays);

	Color* D_Colors;
	cudaMalloc((void**)&D_Colors, Width * Height * sizeof(Color));

	Sphere* D_Spheres;
	cudaMalloc((void**)&D_Spheres, Sphere_Amount * sizeof(Sphere));
	cudaMemcpy(D_Spheres, H_Spheres, Sphere_Amount* sizeof(Sphere), cudaMemcpyHostToDevice);

	cudaDeviceSynchronize();

	const int blockSizeX = 32;
	const int blockSizeY = 32;
	const dim3 blockSize(blockSizeX, blockSizeY, 1);
	const dim3 gridSize(Width / blockSizeX + 1, Height / blockSizeY + 1, 1);

	GetSphereIntersectionKernel << < gridSize, blockSize >> >(D_Rays, D_Spheres, Sphere_Amount, Width, Height, D_Colors);


	cudaMemcpy(H_Colors, D_Colors, Width*Height * sizeof(Color), cudaMemcpyDeviceToHost);

	cudaDeviceSynchronize();

	//declare a temporary color variable
	Color c;

	//Loop through image and set all pixels to red
	for (int x = 0; x < Width; x++){
		for (int y = 0; y < Height; y++)
		{
			c.R = 0;

			c.G = 0;
			c.B = 255;
			c.A = 255;
			//H_Colors[y*Width + x] = c;
			//std::cout << H_Colors[y*Width + x].ToString().c_str() << endl;
		}
	}

	cudaFree(D_Rays);
	cudaFree(D_Colors);
	cudaFree(D_Spheres);
}
