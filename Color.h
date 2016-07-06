#pragma once
#include "CudaDefines.h"
#include <string>
struct Color{
	uchar R;
	uchar G;
	uchar B;
	uchar A;

	Color() :R(0), G(0), B(0), A(0){
	}

	Color(uchar InR, uchar InG, uchar InB, uchar InA):R(InR),G(InG),B(InB),A(InA){

	}

	std::string ToString(){
		std::string s;
		s = "Color: ";
		s += "R: " + std::to_string(static_cast<unsigned int>(R)) + " ";
		s += "G: " + std::to_string(static_cast<unsigned int>(G)) + " ";
		s += "B: " + std::to_string(static_cast<unsigned int>(B)) + " ";
		s += "A: " + std::to_string(static_cast<unsigned int>(A)) + "\n";

		return s;
	}

};