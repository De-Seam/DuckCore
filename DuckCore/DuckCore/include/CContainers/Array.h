#pragma once
#include <CAllocators/HeapAllocator.h>

#include <CUtilities/Assert.h>

// std includes
#include <utility>
#include <cstring>

template<typename taValue, typename taAllocator = HeapAllocator<taValue>>
class Array
{
public:
	Array(uint32 inInitialCapacity = 12);
	~Array();

	Array(Array&& inArray);

	taValue* GetData() { return mData; }
	const taValue* GetData() const { return mData; }

	uint32 GetSize() const { return mSize; }
	uint32 GetCapacity() const { return mCapacity; }

	template<typename... taArgs>
	uint32 Add(taArgs&&... inArgs);
	void Remove(uint32 inIndex);
	void Clear();

	template<typename taLambda>
	int32 FindIf(taLambda&& inLambda) const;
	template<typename taLambda>
	int32 FindIf(taLambda&& inLambda, taValue* outValue) const;
	taValue& Get(uint32 inIndex);
	const taValue& Get(uint32 inIndex) const;
	taValue& operator[](uint32 inIndex);
	const taValue& operator[](uint32 inIndex) const;

private:
	void Expand(uint32 inNewCapacity);
	void Shrink(uint32 inNewCapacity);
	void ResizeCapacity(uint32 inNewCapacity);

private:
	taValue* mData = nullptr;
	uint32 mSize = 0;
	uint32 mCapacity = 0;
	taAllocator mAllocator;
};

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
	mAllocator = std::move(inArray.mAllocator);
}

template<typename taValue, typename taAllocator>
template<typename... taArgs>
inline uint32 Array<taValue, taAllocator>::Add(taArgs && ...inArgs)
{
	if (mSize == mCapacity)
	{
		Expand(mCapacity * 2);
	}

	new (&mData[mSize]) taValue(std::forward<taArgs>(inArgs)...);
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
		taValue& data = mData[i];
		data.~taValue();
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