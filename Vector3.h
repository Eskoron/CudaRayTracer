#pragma once
#include "CudaDefines.h"
#include "RMath.h"

struct Vector3{
	float X;
	float Y;
	float Z;
	 
	hostdevice forceinline Vector3() :X(0.0f), Y(0.0f), Z(0.0f){}

	hostdevice forceinline Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ){}

	hostdevice forceinline void UnsafeNormalize();

	hostdevice forceinline float Size() const;

	hostdevice forceinline float SizeSquared() const;

	hostdevice forceinline static float DotProduct(const Vector3& A, const Vector3& B);

	hostdevice forceinline static Vector3 CrossProduct(const Vector3& A, const Vector3& B);

	//Dot-Product
	hostdevice forceinline float operator|(const Vector3& V)const;

	//Cross Product
	hostdevice forceinline Vector3 operator%(const Vector3& V)const;

	hostdevice forceinline Vector3 operator-(const Vector3& V) const;

	hostdevice forceinline Vector3 operator+(const Vector3& V) const;

	hostdevice forceinline Vector3 operator*(const Vector3& V) const;
};

hostdevice forceinline float Vector3::SizeSquared() const{
	return (X*X+Y*Y+Z*Z);
}

hostdevice forceinline float Vector3::Size() const{
		return RMath::Sqrt(SizeSquared());
}

hostdevice forceinline void Vector3::UnsafeNormalize(){
	float InvertedLength = RMath::Invert(Size());
	X *= InvertedLength;
	Y *= InvertedLength;
	Z *= InvertedLength;
}

hostdevice forceinline float Vector3::DotProduct(const Vector3 &A, const Vector3 &B){
    return A|B;
}

hostdevice forceinline float Vector3::operator|(const Vector3& V)const{
	return X*V.X + Y*V.Y + Z*V.Z;
}

hostdevice forceinline Vector3 Vector3::operator-(const Vector3& V) const{
	return Vector3(X - V.X, Y - V.Y, Z - V.Z);
}

hostdevice forceinline Vector3 Vector3::operator+(const Vector3& V) const{
	return Vector3(X + V.X, Y + V.Y, Z + V.Z);
}

hostdevice forceinline Vector3 Vector3::operator*(const Vector3& V) const{
	return Vector3(X * V.X, Y * V.Y, Z * V.Z);
}

hostdevice forceinline Vector3  Vector3::CrossProduct(const Vector3& A, const Vector3& B){
	return A%B;
}

hostdevice forceinline Vector3 Vector3::operator%(const Vector3& V)const{
	return Vector3(Y * V.Z - Z * V.Y,
		Z * V.X - X * V.Z,
		X * V.Y - Y * V.X);
}

