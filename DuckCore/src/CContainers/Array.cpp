#include <CContainers/Array.h>

// Std includes
#include <cstring>
#include <utility>

template<typename taValue, typename taAllocator>
inline void Array<taValue, taAllocator>::ResizeCapacity(uint32 inNewCapacity)
{
	gAssert(inNewCapacity != mCapacity);
	if (inNewCapacity > mCapacity)
		Expand(inNewCapacity);
	else if (inNewCapacity < mCapacity)
		Shrink(inNewCapacity);
}