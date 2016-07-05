#include "CudaDefines.h"

#include "Vector3.h"
#include "Rotator.h"


struct Matrix44{

	float M[16];

	forceinline explicit Matrix44(float fill = 0.f);

	forceinline Matrix44(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	forceinline hostdevice void TransformVector(Vector3& V)const;
};

forceinline hostdevice void Matrix44::TransformVector(Vector3& V) const{
	float[3] = 
}