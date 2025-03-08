#pragma once
#include <DuckCore/Containers/String.h>
#include <DuckCore/Core/Types.h>

namespace DC
{
// WangHash
uint32 WangHash(uint32 inSeed);
float WangHashF(uint32 inSeed); // Return value between 0.f and 1.f

// XorShift32
uint32 XorShift32(uint32* ioState);
float XorShift32F(uint32* ioState); // Return value between 0.f and 1.f

uint32 Hash(const String& aString);
uint32 Hash(const char* aString);
}
