#include <DuckCore/Math/RGBA.h>

#include <DuckCore/Core/Assert.h>

namespace DC
{
RGBA RGBA::sFromFloats(float aR, float aG, float aB, float aA)
{
	gAssert(aR >= 0.0f && aR <= 1.0f);
	gAssert(aG >= 0.0f && aG <= 1.0f);
	gAssert(aB >= 0.0f && aB <= 1.0f);
	gAssert(aA >= 0.0f && aA <= 1.0f);

	return RGBA
	(
		static_cast<uint8>(aR * 255),
		static_cast<uint8>(aG * 255), 
		static_cast<uint8>(aB * 255), 
		static_cast<uint8>(aA * 255)
	);
}
}
