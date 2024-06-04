#include <CAllocators/HeapAllocator.h>

// Std includes
#include <cstdlib>

template<typename taType>
taType* HeapAllocator<taType>::Allocate()
{
	return malloc(sizeof(taType));
}

template<typename taType>
void HeapAllocator<taType>::Free(taType* inPtr)
{
	free(inPtr);
}
