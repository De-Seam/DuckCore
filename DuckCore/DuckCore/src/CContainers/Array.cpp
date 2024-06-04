#include <CContainers/Array.h>

#include <CUtilities/Assert.h>

// Std includes
#include <cstring>

template<typename taValue, typename taAllocator>
Array<taValue, taAllocator>::Array(uint32 inInitialCapacity)
{
	mData = mAllocator.Allocate(inInitialCapacity);
	mCapacity = inInitialCapacity;
}

template<typename taValue, typename taAllocator>
Array<taValue, taAllocator>::~Array()
{
	Clear();
	mAllocator.Free(mData);
}

template<typename taValue, typename taAllocator>
Array<taValue, taAllocator>::Array(Array&& inArray)
{
	mData = inArray.mData;
	mSize = inArray.mSize;
	mCapacity = inArray.mCapacity;
	mAlloactor = std::move(inArray.mAllocator);
}

template<typename taValue, typename taAllocator>
uint32 Array<taValue, taAllocator>::Add(const taValue& inValue)
{
	if (mSize == mCapacity)
	{
		Expand(mCapacity * 2);
	}

	new (&mData[mSize]) taValue(inValue);
	mSize++;
	return mSize - 1;
}

template<typename taValue, typename taAllocator>
void Array<taValue, taAllocator>::Remove(uint32 inIndex)
{
	gAssert(inIndex < mSize);
	taValue* data = mData[inIndex];
	data->~taValue();
	for (uint32 i = inIndex; i < mSize - 1; ++i)
		mData[i] = mData[i + 1];
	mSize--;
}

template<typename taValue, typename taAllocator>
void Array<taValue, taAllocator>::Clear()
{
	for (uint32 i = 0; i < mSize; ++i)
	{
		taValue* data = mData[i];
		data->~taValue();
	}
}

template<typename taValue, typename taAllocator>
template<typename taLambda>
inline int32 Array<taValue, taAllocator>::FindIf(taLambda&& inLambda) const
{
	for (uint32 i = 0; i < mSize; ++i)
	{
		if (inLambda(mData[i]))
			return i;
	}
	return -1;
}

template<typename taValue, typename taAllocator>
template<typename taLambda>
int32 Array<taValue, taAllocator>::FindIf(taLambda&& inLambda, taValue* outValue) const
{
	for (uint32 i = 0; i < mSize; ++i)
	{
		if (inLambda(mData[i]))
		{
			outValue = &mData[i];
			return i;
		}
	}
	return -1;
}

template<typename taValue, typename taAllocator>
taValue& Array<taValue, taAllocator>::Get(uint32 inIndex)
{
	gAssert(inIndex < mSize);
	return mData[inIndex];
}

template<typename taValue, typename taAllocator>
const taValue& Array<taValue, taAllocator>::Get(uint32 inIndex) const
{
	gAssert(inIndex < mSize);
	return mData[inIndex];
}

template<typename taValue, typename taAllocator>
taValue& Array<taValue, taAllocator>::operator[](uint32 inIndex)
{
	return Get(inIndex);
}

template<typename taValue, typename taAllocator>
const taValue& Array<taValue, taAllocator>::operator[](uint32 inIndex) const
{
	return Get(inIndex);
}

template<typename taValue, typename taAllocator>
void Array<taValue, taAllocator>::Expand(uint32 inNewCapacity)
{
	gAssert(inNewCapacity > mCapacity);
	taValue* new_data = mAllocator.Allocate(inNewCapacity);
	memcpy(new_data, mData, mSize * sizeof(taValue));
	mAllocator.Free(mData);
	mData = new_data;
	mCapacity = inNewCapacity;
}

template<typename taValue, typename taAllocator>
void Array<taValue, taAllocator>::Shrink(uint32 inNewCapacity)
{
	gAssert(inNewCapacity < mCapacity);
	for (uint32 i = inNewCapacity; i < mCapacity; i++)
	{
		taValue* data = mData[i];
		if (i < mSize)
			data->~taValue();
		mAllocator.Free(data);
	}
	taValue* new_data = mAllocator.Allocate(inNewCapacity);
	memcpy(new_data, mData, inNewCapacity * sizeof(taValue));
	mAllocator.Free(mData);
	mData = new_data;
	mCapacity = inNewCapacity;
	if (mSize > mCapacity)
			mSize = mCapacity;
}

template<typename taValue, typename taAllocator>
inline void Array<taValue, taAllocator>::ResizeCapacity(uint32 inNewCapacity)
{
	gAssert(inNewCapacity != mCapacity);
	if (inNewCapacity > mCapacity)
		Expand(inNewCapacity);
	else (inNewCapacity < mCapacity)
		Shrink(inNewCapacity);
}