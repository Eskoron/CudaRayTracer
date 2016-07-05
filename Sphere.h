#pragma once
#include "Vector3.h"
#include "CudaDefines.h"
#include "Ray.h"
#include "Vector3.h"
#include "RMath.h"
struct Sphere{

	Vector3 Position;
	float Radius;

	forceinline hostdevice float intersectRay(const Ray& R, float& dist) const{
		float t0, t1;

		Vector3 L = R.Origin - Position;
		float a = R.Direction | R.Direction;
		float b = 2 * (R.Direction | L);
		float c = (L | L) - Radius;
		if (!RMath::SolveQuadratic(a, b, c, t0, t1)) return false;

		if (t0 < 0) {
			//t0 = t1; // if t0 is negative, let's use t1 instead
			//if (t0 < 0)
			return false; // both t0 and t1 are negative
		}

		if (t0<dist){
			dist = t0;
			return true;
		}
		else{
			return false;
		}


	}

};

