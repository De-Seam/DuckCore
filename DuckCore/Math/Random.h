#pragma once
// Core includes
#include "DuckCore/Core/Types.h"

namespace DC
{

// WangHash
uint32 gWangHash(uint32 inSeed);
float gWangHashF(uint32 inSeed); // Return value between 0.f and 1.f

// XorShift32
uint32 gXorShift32(uint32* ioState);
float gXorShift32F(uint32* ioState); // Return value between 0.f and 1.f

}
