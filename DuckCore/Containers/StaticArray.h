#pragma once
// Core includes
#include <DuckCore/Core/Types.h>

// Std includes
#include <array>

namespace DC
{
template<typename taType, int taSize>
class StaticArray
{
public:
	StaticArray() = default;
	StaticArray(std::initializer_list<taType> inList);

	taType& operator[](int inIndex) { return At(inIndex); }
	const taType& operator[](int inIndex) const { return At(inIndex); }
	taType& At(int inIndex) { return mArray[inIndex]; }
	const taType& At(int inIndex) const { return mArray[inIndex]; }

	int Length() const { return static_cast<int>(mArray.size()); }

	int Find(const taType& inValue) const;
	template<typename taPredicate>
	int FindIf(taPredicate&& inPredicate) const; // Returns index where the predicate evaluated to true

	bool Contains(const taType& inValue) const { return Find(inValue) != -1; }

	taType& Front() { return mArray.front(); }
	const taType& Front() const { return mArray.front(); }
	taType& Back() { return mArray.back(); }
	const taType& Back() const { return mArray.back(); }

	taType* Data() { return mArray.data(); }
	const taType* Data() const { return mArray.data(); }

	// Custom iterator support
    typename std::array<taType, taSize>::iterator begin() { return mArray.begin(); }
    typename std::array<taType, taSize>::iterator end() { return mArray.end(); }

    typename std::array<taType, taSize>::const_iterator begin() const { return mArray.begin(); }
    typename std::array<taType, taSize>::const_iterator end() const { return mArray.end(); }

    typename std::array<taType, taSize>::const_iterator cbegin() const { return mArray.cbegin(); }
    typename std::array<taType, taSize>::const_iterator cend() const { return mArray.cend(); }

private:
	std::array<taType, taSize> mArray;
};

template<typename taType, int taSize>
StaticArray<taType, taSize>::StaticArray(std::initializer_list<taType> inList)
{
	gAssert(inList.size() == Length(), "Initializer list should be of the same length as the static array. Otherwise it should not be used, to prevent uninitialized memory.");
	for (int i = 0; i < Length(); i++)
		mArray[i] = *(inList.begin() + i);
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
