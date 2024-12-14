#pragma once
// Core includes
#include <DuckCore/Core/Types.h>

// Std includes
#include <array>

namespace DC
{
template<typename taType, int taLength>
class StaticArray
{
	static_assert(taLength >= 1, "Length must be 1 or higher.");

public:
	StaticArray() = default;
	StaticArray(std::initializer_list<taType> inList);

	taType& operator[](int inIndex) { return At(inIndex); }
	const taType& operator[](int inIndex) const { return At(inIndex); }
	taType& At(int inIndex) { gAssert(IsValidIndex(inIndex)); return mData[inIndex]; }
	const taType& At(int inIndex) const { gAssert(IsValidIndex(inIndex)); return mData[inIndex]; }

	int Length() const { return taLength; }
	int IsValidIndex(int inIndex) const { return inIndex >= 0 && inIndex < Length(); }

	int Find(const taType& inValue) const;
	template<typename taPredicate>
	int FindIf(taPredicate&& inPredicate) const; // Returns index where the predicate evaluated to true

	bool Contains(const taType& inValue) const { return Find(inValue) != -1; }

	taType& Front() { return mData[0]; }
	const taType& Front() const { return mData[0]; }
	taType& Back() { return mData[taLength-1]; }
	const taType& Back() const { return mData[taLength-1]; }

	taType* Data() { return mData; }
	const taType* Data() const { return mData; }

	// Iterator support
    taType* begin() { return mData; }
    taType* end() { return mData + taLength; }
    const taType* begin() const { return mData; }
    const taType* end() const { return mData + taLength; }
    const taType* cbegin() const { return mData; }
    const taType* cend() const { return mData + taLength; }

private:
	taType mData[taLength];
};

template<typename taType, int taSize>
StaticArray<taType, taSize>::StaticArray(std::initializer_list<taType> inList)
{
	gAssert(inList.size() == Length(), "Initializer list should be of the same length as the static array. Otherwise it should not be used, to prevent uninitialized memory.");
	for (int i = 0; i < Length(); i++)
		mData[i] = *(inList.begin() + i);
}

template<typename taType, int taSize>
inline int StaticArray<taType,taSize>::Find(const taType& inValue) const 
{
	for (int i = 0; i < Length(); i++)
	{
		if (inValue == At(i))
			return i;
	}
	return -1;
}

template<typename taType, int taSize>
template<typename taPredicate>
inline int StaticArray<taType, taSize>::FindIf(taPredicate&& inPredicate) const
{
	for (int i = 0; i < Length(); i++)
	{
		if (inPredicate(At(i)))
			return i;
	}
	return -1;
}
}
