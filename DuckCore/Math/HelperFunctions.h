#pragma once
namespace DC
{

constexpr double gPi()
{
	return 3.14159265358979323846;
}

constexpr float gPiF()
{
	return 3.14159265358979323846f;
}

inline double gToRadians(double inDegrees)
{
	return inDegrees * 0.01745329251994329576923690768489;
}

inline float gToRadiansF(float inDegrees)
{
	return inDegrees * 0.01745329251994329576923690768489f;
}

inline double gToDegrees(double inRadians)
{
	return inRadians * 57.295779513082320876798154814105;
}

inline float gToDegreesF(float inRadians)
{
	return inRadians * 57.295779513082320876798154814105f;
}

template<typename taType>
inline taType gLerp(taType a, taType b, taType t)
{
	return a + (b - a) * t;
}

template<typename taType>
inline taType gMin(const taType& inA, const taType& inB)
{
	return inA < inB ? inA : inB;
}

template<typename taType>
inline taType gMax(const taType& inA, const taType& inB)
{
	return inA > inB ? inA : inB;
}

template<typename taType>
inline taType gClamp(const taType& inValue, const taType& inMin, const taType& inMax)
{
	return gMin(gMax(inValue, inMin), inMax);
}

}