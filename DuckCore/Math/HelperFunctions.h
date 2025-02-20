#pragma once
namespace DC
{

static constexpr float cPiF = 3.14159265358979323846f;
static constexpr double cPi = 3.14159265358979323846;

inline float DegreesToRadians(float aDegrees);
inline double DegreesToRadians(double aDegrees);

inline float RadiansToDegrees(float aRadians);
inline double RadiansToDegrees(double aRadians);

inline float Sqrt(float aValue);
inline double Sqrt(double aValue);

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