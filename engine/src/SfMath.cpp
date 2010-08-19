#include "SfMath.h"

float RADTODEG(const float Radians)
{ 
	return Radians * 180.0f / PI; 
}

float DEGTORAD(const float Degrees)
{ 
	return Degrees * PI / 180.0f; 
}