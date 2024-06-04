#pragma once
#include <CAllocators/AllocatorBase.h>

template<typename taType>
class HeapAllocator : public AllocatorBase<taType>
{
public:
	virtual taType* Allocate();
	virtual void Free(taType* inPtr);
};