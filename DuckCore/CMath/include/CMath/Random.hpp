#pragma once
#include <CMath/Types.hpp>

//Random functions
inline uint32 gWangHash(uint32 seed)
{
	seed = (seed ^ 61) ^ (seed >> 16);
	seed *= 9;
	seed = seed ^ (seed >> 4);
	seed *= 0x27d4eb2d;
	seed = seed ^ (seed >> 15);
	return seed;
}

inline float gWangHashF(uint32 seed) // Return value between 0.f amd 1.f
{
	return gWangHash(seed) * (1.0f / 4294967296.0f);
}

inline uint32 gXorShift32(uint32* pstate)
{
	// Xorshift algorithm from George Marsaglia's paper
	uint32 state = *pstate;
	state ^= (state << 13);
	state ^= (state >> 17);
	state ^= (state << 5);
	return (*pstate) = state;
}

inline float gXorShift32F(uint32* state) // Return value between 0.f and 1.f
{
	return gXorShift32(state) * (1.0f / 4294967296.0f);
}