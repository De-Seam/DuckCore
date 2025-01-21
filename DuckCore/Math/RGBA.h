#pragma once
#include <DuckCore/Core/Types.h>

#pragma warning (push)
#pragma warning (disable : 4201) //to avoid nameless struct / union warning.

namespace DC
{
	struct RGBA
	{
		explicit RGBA(uint32 inRGBA): mRGBA(inRGBA) {}
		explicit RGBA(uint8 inR, uint8 inG, uint8 inB, uint8 inA) : mR(inR), mG(inG), mB(inB), mA(inA) {}
		explicit RGBA(float inR, float inG, float inB, float inA);

		union
		{
			struct
			{
				uint8 mR, mG, mB, mA;
			};
			uint32 mRGBA;
		};
	};
}

#pragma warning (pop)