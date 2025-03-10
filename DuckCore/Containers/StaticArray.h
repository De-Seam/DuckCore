#pragma once
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Core/Types.h>

#include <initializer_list>

namespace DC
{
template<typename taType, int taLength>
class StaticArray
{
	static_assert(taLength >= 1, "Length must be 1 or higher.");

public:
	StaticArray() = default;
	StaticArray(std::initializer_list<taType> aList);

	taType& operator[](int aIndex) { return At(aIndex); }
	const taType& operator[](int aIndex) const { return At(aIndex); }
	taType& At(int aIndex) { gAssert(IsValidIndex(aIndex)); return mData[aIndex]; }
	const taType& At(int aIndex) const { gAssert(IsValidIndex(aIndex)); return mData[aIndex]; }

	void Fill(const taType& aValue) { for (int i = 0; i < Length(); i++) mData[i] = aValue; }

	int Length() const { return taLength; }
	int IsValidIndex(int aIndex) const { return aIndex >= 0 && aIndex < Length(); }

	int Find(const taType& aValue) const;
	template<typename taPredicate>
	int FindIf(taPredicate&& aPredicate) const; // Returns index where the predicate evaluated to true

	bool Contains(const taType& aValue) const { return Find(aValue) != -1; }

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
StaticArray<taType, taSize>::StaticArray(std::initializer_list<taType> aList)
{
	gAssert(aList.size() == Length(), "Initializer list should be of the same length as the static array. Otherwise it should not be used, to prevent uninitialized memory.");
	for (int i = 0; i < Length(); i++)
		mData[i] = *(aList.begin() + i);
}

template<typename taType, int taSize>
inline int StaticArray<taType,taSize>::Find(const taType& aValue) const 
{
	for (int i = 0; i < Length(); i++)
	{
		if (aValue == At(i))
			return i;
	}
	return -1;
}

template<typename taType, int taSize>
template<typename taPredicate>
inline int StaticArray<taType, taSize>::FindIf(taPredicate&& aPredicate) const
{
	for (int i = 0; i < Length(); i++)
	{
		if (aPredicate(At(i)))
			return i;
	}
	return -1;
}
}
