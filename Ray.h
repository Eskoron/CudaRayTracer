#pragma once
#include "Vector3.h"
#include "CudaDefines.h"
struct Ray{
	Vector3 Origin;
	Vector3 Direction;

	forceinline Ray(Vector3 InOrigin, Vector3 InDirection) :Origin(InOrigin), Direction(InDirection){}

	forceinline void Print(){
		printf("\n Ray: Position: %f %f %f, Direction: %f %f %f", Origin.X, Origin.Y, Origin.Z, Direction.X, Direction.Y, Direction.Z);
	}
};