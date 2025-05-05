#pragma once
#include <DuckCore/Core/Types.h>

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable : 4201) //to avoid nameless struct / union warning.
#elif defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#else
    #error "Unsupported compiler"
#endif

namespace DC
{
	struct RGBA
	{
		explicit RGBA(uint32 inRGBA): mRGBA(inRGBA) {}
		explicit RGBA(uint8 aR, uint8 aG, uint8 aB, uint8 aA) : mR(aR), mG(aG), mB(aB), mA(aA) {}

		union
		{
			struct
			{
				uint8 mR, mG, mB, mA;
			};
			uint32 mRGBA;
		};

		static RGBA sFromFloats(float aR, float aG, float aB, float aA);
		static RGBA sBlack() { return RGBA(0, 0, 0, 255); }
		static RGBA sWhite() { return RGBA(255, 255, 255, 255); }
	};
}

#ifdef _MSC_VER
    #pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#else
    #error "Unsupported compiler"
#endif