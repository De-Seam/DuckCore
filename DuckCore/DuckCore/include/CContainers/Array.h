#pragma once
#include <CAllocators/HeapAllocator.h>

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

	uint32 Add(const taValue& inValue);
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
