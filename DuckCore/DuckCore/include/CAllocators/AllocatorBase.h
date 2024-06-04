#pragma once
#include <CCore/Types.h>

template<typename taType>
class AllocatorBase
{
public:
	virtual taType* Allocate() = 0;
	virtual void Free(taType* inPtr) = 0;

protected:
	// TODO: Implement
	void TrackAllocation(taType* inPtr);
	void UntrackAllocation(taType* inPtr);

private:
};