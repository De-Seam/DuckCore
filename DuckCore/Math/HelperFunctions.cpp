#include <DuckCore/Math/HelperFunctions.h>

#include <cmath>

namespace DC
{
double DegreesToRadians(double aDegrees)
{
	return aDegrees * 0.01745329251994329576923690768489;
}

float DegreesToRadians(float aDegrees)
{
	return aDegrees * 0.01745329251994329576923690768489f;
}

double RadiansToDegrees(double aRadians)
{
	return aRadians * 57.295779513082320876798154814105;
}

float RadiansToDegrees(float aRadians)
{
	return aRadians * 57.295779513082320876798154814105f;
}

float Sqrt(float aValue)
{
#ifdef _WIN32
	return std::sqrtf(aValue);
#elif __linux__
return std::sqrt(aValue);
#endif
}

double Sqrt(double aValue)
{
	return std::sqrt(aValue);
}
}
