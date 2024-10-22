#pragma once
#include <CAllocators/AllocatorBase.h>

// std includes
#include <cstdlib>

template<typename taType>
class HeapAllocator : public AllocatorBase<taType>
{
public:
	virtual taType* Allocate(uint32 inCount = 1);
	virtual void Free(taType* inPtr);
};

template<typename taType>
taType* HeapAllocator<taType>::Allocate(uint32 inCount)
{
	return reinterpret_cast<taType*>(malloc(inCount * sizeof(taType)));
}

template<typename taType>
void HeapAllocator<taType>::Free(taType* inPtr)
{
	free(inPtr);
}
