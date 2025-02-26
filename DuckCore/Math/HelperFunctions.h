#pragma once
namespace DC
{

static constexpr float cPiF = 3.14159265358979323846f;
static constexpr double cPi = 3.14159265358979323846;

float DegreesToRadians(float aDegrees);
double DegreesToRadians(double aDegrees);

float RadiansToDegrees(float aRadians);
double RadiansToDegrees(double aRadians);

float Sqrt(float aValue);
double Sqrt(double aValue);

template<typename taType>
inline taType Lerp(taType aFrom, taType aTo, taType aT)
{
	return aFrom + (aTo - aFrom) * aT;
}

template<typename taType>
inline taType Min(const taType& aA, const taType& aB)
{
	return aA < aB ? aA : aB;
}

template<typename taType>
inline taType Max(const taType& aA, const taType& aB)
{
	return aA > aB ? aA : aB;
}

template<typename taType>
inline taType Clamp(const taType& aValue, const taType& aMin, const taType& aMax)
{
	return Min(Max(aValue, aMin), aMax);
}

}