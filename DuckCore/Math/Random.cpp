#include <DuckCore/Math/Random.h>

namespace DC
{
uint32 WangHash(uint32 inSeed)
{
	inSeed = (inSeed ^ 61) ^ (inSeed >> 16);
	inSeed *= 9;
	inSeed = inSeed ^ (inSeed >> 4);
	inSeed *= 0x27d4eb2d;
	inSeed = inSeed ^ (inSeed >> 15);
	return inSeed;
}

float WangHashF(uint32 inSeed)
{
	return gStaticCast<float>(WangHash(inSeed)) * (1.0f / 4294967296.0f);
}

uint32 XorShift32(uint32* ioState)
{
	// Xorshift algorithm from George Marsaglia's paper
	uint32 state = *ioState;
	state ^= (state << 13);
	state ^= (state >> 17);
	state ^= (state << 5);
	return (*ioState) = state;
}

float XorShift32F(uint32* ioState)
{
	return gStaticCast<float>(XorShift32(ioState)) * (1.0f / 4294967296.0f);
}

uint32 Hash(const String& aString)
{
	uint32 hash = 0x811C9DC5; // Initial seed (can be any non-zero value)

	for (int i = 0; i < aString.Length(); i++)
	{
		char character = aString[i];
        hash ^= gStaticCast<uint32>(character);
        hash ^= (hash << 13);
        hash ^= (hash >> 17);
        hash ^= (hash << 5);
    }
	return hash;
}

uint32 Hash(const char* aString)
{
	uint32 hash = 0x811C9DC5; // Initial seed (can be any non-zero value)

	for (const char* character = aString; *character != '\0'; character++) 
	{
		hash ^= gStaticCast<uint32>(*character);
		hash ^= (hash << 13);
		hash ^= (hash >> 17);
		hash ^= (hash << 5);
	}
	return hash;
}
}
