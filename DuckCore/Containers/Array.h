#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Math/HelperFunctions.h>
#include <DuckCore/Utilities/Utilities.h>

namespace DC
{

template<typename taType>
class Array
{
public:
	static constexpr int cBaseCapacity = 12; // The capacity the Array will consume during its first allocation.

	Array() = default;
	~Array();

	taType& operator[](int aIndex) { return At(aIndex); }
	const taType& operator[](int aIndex) const { return At(aIndex); }
	taType& At(int aIndex) { gAssert(IsValidIndex(aIndex)); return mData[aIndex]; }
	const taType& At(int aIndex) const { gAssert(IsValidIndex(aIndex)); return mData[aIndex]; }

	void Resize(int aLength); // Resize, calling the new operator on new elements.
	void Reserve(int aCapacity); // Reserve capacity. This will not change the length of the array.
	void ShrinkToFit();

	int Length() const { return mLength; }
	bool IsEmpty() const { return Length() == 0; }

	bool IsValidIndex(int inIndex) const { return inIndex >= 0 && inIndex < Length(); }

	void Clear();
	void Add(taType inValue);
	template<typename... taArgs>
	void Emplace(taArgs&&... inArgs);

	void PopBack();

	void Remove(int inIndex);
	void SwapRemove(int inIndex);
	template<typename taPredicate>
	int RemoveIf(taPredicate&& inPredicate); // Returns amount removed
	template<typename taPredicate>
	int SwapRemoveIf(taPredicate&& inPredicate); // Returns amount removed
	template<typename taPredicate>
	bool RemoveFirstIf(taPredicate&& inPredicate); // Returns whether any were removed
	template<typename taPredicate>
	bool ReverseRemoveFirstIf(taPredicate&& inPredicate); // Returns whether any were removed
	template<typename taPredicate>
	bool SwapRemoveFirstIf(taPredicate&& inPredicate); // Returns whether any were removed
	template<typename taPredicate>
	bool ReverseSwapRemoveFirstIf(taPredicate&& inPredicate); // Returns whether any were removed

	int Find(const taType& inValue) const;
	template<typename taOtherType>
	int Find(const taOtherType& inValue) const;
	template<typename taPredicate>
	int FindIf(taPredicate&& inPredicate) const; // Returns index where the predicate evaluated to true

	bool Contains(const taType& inValue) const { return Find(inValue) != -1; }
	template<typename taOtherType>
	bool Contains(const taOtherType& inValue) const { return Find(inValue) != -1; }

	taType& Front() { gAssert(!IsEmpty()); return mData[0]; }
	const taType& Front() const { gAssert(!IsEmpty()); return mData[0]; }
	taType& Back() { gAssert(!IsEmpty()); return mData[mLength-1]; }
	const taType& Back() const { gAssert(!IsEmpty()); return mData[mLength-1]; }

	taType* Data() { return mData; }
	const taType* Data() const { return mData; }

	// Iterator support
	taType* begin() { return mData; }
	taType* end() { return mData + mLength; }
	const taType* begin() const { return mData; }
	const taType* end() const { return mData + mLength; }
	const taType* cbegin() const { return mData; }
	const taType* cend() const { return mData + mLength; }

private:
	int mLength = 0;
	int mCapacity = 0;
	taType* mData = nullptr;
};

template <typename taType>
Array<taType>::~Array()
{
	if (mData != nullptr)
	{
		gAssert(mCapacity > 0);
		Clear();
		free(mData);
		mData = nullptr;
		mCapacity = 0;
	}
}

template<typename taType>
void Array<taType>::Resize(int aLength)
{
	if (aLength > mLength)
	{
		// Reserve length if needed. Reserve already checks internally if the capacity is already enough.
		Reserve(aLength);

		// Call new operators on new elements.
		for (int i = mLength; i < aLength; i++)
			new (&mData[i]) taType();
	}
	else
	{
		// Call destructors on elements that are being removed. We keep the capacity.
		for (int i = aLength; i < mLength; i++)
			mData[i].~taType();
	}
	mLength = aLength;
}

template<typename taType>
void Array<taType>::Reserve(int aCapacity)
{
	gAssert(aCapacity > 0, "Arrays need to have a capacity of 1 or higher.");

	// Early out if we're already at or above the requested capacity.
	if (aCapacity <= mCapacity)
		return;

	taType* new_data = gStaticCast<taType*>(malloc(aCapacity * sizeof(taType)));
	gAssert(new_data != nullptr);

	// Move-construct existing elements into new memory
	for (int i = 0; i < mLength; i++)
	{
		new (&new_data[i]) taType(Move(mData[i]));
		mData[i].~taType(); // Destroy old element
	}

	if (mData != nullptr)
		free(mData);
	mData = new_data;
	mCapacity = aCapacity;
}

template<typename taType>
void Array<taType>::ShrinkToFit()
{
	if (mLength == mCapacity)
		return;

	if (mLength == 0)
	{
		free(mData);
		mData = nullptr;
		mCapacity = 0;

		return;
	}

	taType* new_data = gStaticCast<taType*>(malloc(mLength * sizeof(taType)));

	// Move-construct existing elements into new memory
	for (int i = 0; i < mLength; i++)
	{
		new (&new_data[i]) taType(std::move(mData[i]));
		mData[i].~taType(); // Destroy old element
	}

	free(mData);
	mData = new_data;

	mCapacity = mLength;
}

template<typename taType>
void Array<taType>::Clear()
{
	for (int i = 0; i < mLength; i++)
		mData[i].~taType();

	// Set the length to 0, but keep the capacity.
	mLength = 0;
}

template<typename taType>
void Array<taType>::Add(taType inValue)
{
	if (mLength == mCapacity)
		Reserve(Max(mCapacity * 2, cBaseCapacity));

	new (&mData[mLength]) taType(Move(inValue));
	mLength++;
}

template<typename taType>
template<typename ... taArgs>
void Array<taType>::Emplace(taArgs&&... inArgs)
{
	if (mLength == mCapacity)
		Reserve(Max(mCapacity * 2, cBaseCapacity));

	new (&mData[mLength]) taType(std::forward<taArgs>(inArgs)...);
	mLength++;
}

template<typename taType>
void Array<taType>::PopBack()
{
	gAssert(!IsEmpty());

	mLength--;
	mData[mLength].~taType();
}

template<typename taType>
inline void Array<taType>::Remove(int inIndex)
{
	gAssert(IsValidIndex(inIndex));

	mData[inIndex].~taType();

	for (int i = inIndex; i < mLength - 1; i++)
		mData[i] = Move(mData[i + 1]);

	mLength--;
}

template<typename taType>
void Array<taType>::SwapRemove(int inIndex)
{
	gAssert(IsValidIndex(inIndex));
	gSwap(mData[inIndex], Back());
	PopBack();
}

template<typename taType>
template<typename taPredicate>
inline int Array<taType>::RemoveIf(taPredicate&& inPredicate)
{
	int removed_count = 0;
	// Reverse looping so we can remove items without worrying about changing i mid-loop to accomodate the array shrinking
	for (int i = Length()-1; i >= 0; i--)
	{
		if (inPredicate(At(i)))
		{
			Remove(i);
			removed_count++;
		}
	}
	return removed_count;
}

template<typename taType>
template<typename taPredicate>
int Array<taType>::SwapRemoveIf(taPredicate&& inPredicate)
{
	int removed_count = 0;
	// Reverse looping so we can remove items without worrying about changing i mid-loop to accomodate the array shrinking
	for (int i = 0; i < Length(); i++)
	{
		if (inPredicate(At(i)))
		{
			SwapRemove(i);
			removed_count++;
		}
	}
	return removed_count;
}

template<typename taType>
template<typename taPredicate>
inline bool Array<taType>::RemoveFirstIf(taPredicate&& inPredicate)
{
	for (int i = 0; i < Length(); i++)
	{
		if (inPredicate(At(i)))
		{
			Remove(i);
			return true;
		}
	}
	return false;
}

template<typename taType>
template<typename taPredicate>
bool Array<taType>::ReverseRemoveFirstIf(taPredicate&& inPredicate)
{
	for (int i = Length()-1; i >= 0; i--)
	{
		if (inPredicate(At(i)))
		{
			Remove(i);
			return true;
		}
	}
	return false;
}

template<typename taType>
template<typename taPredicate>
bool Array<taType>::SwapRemoveFirstIf(taPredicate&& inPredicate)
{
	for (int i = 0; i < Length(); i++)
	{
		if (inPredicate(At(i)))
		{
			SwapRemove(i);
			return true;
		}
	}
	return false;
}

template<typename taType>
template<typename taPredicate>
bool Array<taType>::ReverseSwapRemoveFirstIf(taPredicate&& inPredicate)
{
	for (int i = Length()-1; i >= 0; i--)
	{
		if (inPredicate(At(i)))
		{
			SwapRemove(i);
			return true;
		}
	}
	return false;
}

template<typename taType>
inline int Array<taType>::Find(const taType& inValue) const 
{
	for (int i = 0; i < Length(); i++)
	{
		if (inValue == At(i))
			return i;
	}
	return -1;
}

template <typename taType>
template <typename taOtherType>
int Array<taType>::Find(const taOtherType& inValue) const
{
	for (int i = 0; i < Length(); i++)
	{
		if (inValue == At(i))
			return i;
	}
	return -1;
}

template<typename taType>
template<typename taPredicate>
inline int Array<taType>::FindIf(taPredicate&& inPredicate) const
{
	for (int i = 0; i < Length(); i++)
	{
		if (inPredicate(At(i)))
			return i;
	}
	return -1;
}

}
