#ifndef RMATH_H
#define RMATH_H
#include <math.h>
#include <algorithm>
#include "CudaDefines.h"
class RMath{
public:
	//PI
	#define PI 3.1415926535897932f


	hostdevice forceinline static bool SolveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
	{
		float discr = b * b - 4 * a * c;
		if (discr < 0) return false;
		else if (discr == 0) x0 = x1 = -0.5f * b / a;
		else {
			float q = (b > 0) ?
				-0.5f * (b + sqrt(discr)) :
				-0.5f * (b - sqrt(discr));
			x0 = q / a;
			x1 = c / q;
		}
		if (x0 > x1){
			float tmP(x0);
			x1 = x0;
			x0 = tmP;
		}

		return true;
	}


	hostdevice forceinline static float Sqrt(float i){
		return sqrtf(i);
	}

	hostdevice forceinline static float Invert(float i){
		return (1.0f / i);
	}

	hostdevice forceinline static float Sin(float i){
		return sinf(i);
	}

	hostdevice forceinline static float Cos(float i){
		return cosf(i);
	}

	hostdevice forceinline static float Tan(float i){
		return tanf(i);
	}

	hostdevice forceinline static float Mod(float i, float* k){
		return modf(i, k);
	}

	hostdevice forceinline static float Abs(float i){
		return abs(i);
	}

	inline static float Min(const float i, const float j){
		return std::min(i, j);
	}

	inline static float Max(const float i, const float j){
		return std::max(i, j);
	}

	 static float Clamp(const float low, const float high, const float i){
		return Max(low, Min(high, i));
	}

	hostdevice forceinline static float DegToRad(const float Degree){
		return Degree * (PI / 180.0f);
	}

	hostdevice forceinline static float RadToDeg(const float Radian){
		return Radian * (180.0f / PI);
	}



};
#endif // RMATH_H
