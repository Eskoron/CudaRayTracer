#pragma once
#include "CudaDefines.h"
#include "Vector3.h"
struct Rotator{

	float Pitch;
	float Yaw;
	float Roll;

	forceinline Rotator():Pitch(0.0f), Yaw(0.0f), Roll(0.0f){}
	
	explicit forceinline Rotator(float InF) : Pitch(InF), Yaw(InF), Roll(InF){}

	forceinline Rotator(float InPitch, float InYaw, float InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll){}


	forceinline hostdevice void RotateVector(Vector3& V) const;
};



forceinline hostdevice void Rotator::RotateVector( Vector3 &V) const{
	//return RotationTranslationMatrix(*this).TransformVector(V);
}