#include <DuckCore/Math/RGBA.h>

#include <DuckCore/Core/Assert.h>

namespace DC
{
RGBA::RGBA(float inR, float inG, float inB, float inA) :
	mR(static_cast<uint8>(inR * 255)), 
	mG(static_cast<uint8>(inG * 255)), 
	mB(static_cast<uint8>(inB * 255)), 
	mA(static_cast<uint8>(inA * 255)) 
{
	gAssert(inR >= 0.0f && inR <= 1.0f);
	gAssert(inG >= 0.0f && inG <= 1.0f);
	gAssert(inB >= 0.0f && inB <= 1.0f);
	gAssert(inA >= 0.0f && inA <= 1.0f);
}
}
