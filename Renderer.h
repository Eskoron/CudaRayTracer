#pragma once
#include "CudaDefines.h"
#include "Ray.h"
#include "Sphere.h"
#include "Image.h"
#include "PerspectiveCamera.h"
struct Renderer{

	uint Width = 100;
	uint Height = 100;

	forceinline Renderer(uint InWidth, uint InHeight):Width(InWidth),Height(InHeight){

	}

	forceinline void Render(PerspectiveCamera* Camera);



	forceinline void RenderSpheres(const Ray* D_Rays, const  Sphere* D_Spheres, const uint AmountSpheres, Color* D_Colors) const;

};

forceinline void Renderer::RenderSpheres(const Ray* D_Rays, const  Sphere* D_Spheres, const uint AmountSpheres, Color* D_Colors) const{

	const int blockSizeX = 32;
	const int blockSizeY = 32;
	const dim3 blockSize(blockSizeX, blockSizeY, 1);
	const dim3 gridSize(Width / blockSizeX + 1, Height / blockSizeY + 1, 1);

	//GetSphereIntersectionKernel <<< gridSize, blockSize >> >(D_Rays, D_Spheres,AmountSpheres, Width,Height, Color* D_Colors);
}

forceinline void Renderer::Render(PerspectiveCamera* Camera){
	
	Ray* D_Rays;
	
	cudaMalloc((void**)&D_Rays, Width * Height * sizeof(Ray));
	

	Camera->GetRays(D_Rays);
	
	
	Color* D_Colors;
	cudaMalloc((void**)&D_Colors, Width * Height * sizeof(Color));
	Color* H_Colors;
	H_Colors = (Color*)malloc(Width * Height * sizeof(Color));



	cudaDeviceSynchronize();



	cudaMemcpy(H_Colors, D_Colors, Width*Height * sizeof(Ray), cudaMemcpyDeviceToHost);



	//declare image
	TGAImage *img = new TGAImage((short)Width, (short)Height);

	//declare a temporary color variable
	Color c;

	//Loop through image and set all pixels to red
	for (int x = 0; x<Width; x++)
		for (int y = 0; y<Height; y++)
		{
				c.R = 0;
			
				c.G = 0;
			c.B = 0;
			c.A = 255;
			img->setPixel(c, x, y);
		}

	//write the image to disk
	string filename = "C:\\Users\\chris\\Documents\\Visual Studio 2013\\Projects\\Cuda\\RayTracer\\test.tga";
	img->WriteImage(filename);

	cudaFree(D_Rays);
	free(H_Colors);

}

forceinline kernel void GetSphereIntersectionKernel(const Ray* D_Rays, const Sphere* D_Spheres, const uint spheres, const float Width, const float Height, Color* c);