
#pragma once
#include "CudaDefines.h"
#include "Vector3.h"
#include "Rotator.h"
#include "Ray.h"

struct PerspectiveCamera{
	Vector3 Position;
	Rotator Rotation;
	float Height;
	float Width;
	float PovAngle;
	float Scale = RMath::Tan(RMath::DegToRad(PovAngle * 0.5));
	float AspectRatioScale = ((float)Width) / ((float)Height) * Scale;


	forceinline PerspectiveCamera(Vector3 InPosition, Rotator InRotation, int InWidth, int InHeight, float InPovAngle) :Position(InPosition), Rotation(InRotation), Height(InHeight), Width(InWidth), PovAngle(InPovAngle){
		Scale = RMath::Tan(RMath::DegToRad(PovAngle * 0.5));
		AspectRatioScale = ((float)Width) / ((float)Height) * Scale;
	}

	forceinline void GetRays(Ray* D_Rays) const;

};

forceinline kernel void GetRaysKernel(const Vector3& position, const Rotator& Rotation, const float Width, const float Height, const float AspectRatioScale, const  float Scale, Ray* D_Ray);

forceinline void PerspectiveCamera::GetRays(Ray* D_Rays) const{
	//Reserve cuda memory
	const int blockSizeX = 32;
	const int blockSizeY = 32;
	const dim3 blockSize(blockSizeX, blockSizeY, 1);
	const dim3 gridSize(Width / blockSizeX + 1, Height / blockSizeY + 1, 1);

	//GetRaysKernel <<< gridSize, blockSize >>>(Position,Rotation, Width, Height, AspectRatioScale, Scale, D_Rays);
};