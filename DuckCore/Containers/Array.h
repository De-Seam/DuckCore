#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Utilities/Utilities.h>

namespace DC
{

template<typename taType>
class Array
{
public:
	Array();

	taType& operator[](int inIndex) { return At(inIndex); }
	const taType& operator[](int inIndex) const { return At(inIndex); }
	taType& At(int inIndex) { gAssert(IsValidIndex(inIndex)); return mData[inIndex]; }
	const taType& At(int inIndex) const { gAssert(IsValidIndex(inIndex)); return mData[inIndex]; }

	void Resize(int inLength); // Resize, calling the new operator on new elements.
	void Reserve(int inCapacity); // Reserve capacity. This will not change the length of the array.
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
	template<typename taPredicate>
	int FindIf(taPredicate&& inPredicate) const; // Returns index where the predicate evaluated to true

	bool Contains(const taType& inValue) const { return Find(inValue) != -1; }

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
	int mCapacity = 12; // Default capacity is 12. Capacity is not initialized with new.
	taType* mData = nullptr; // This will never be nullptr after the constructor.
};

template<typename taType>
Array<taType>::Array()
{
	mData = gStaticCast<taType*>(malloc(mCapacity * sizeof(taType)));
}

template<typename taType>
void Array<taType>::Resize(int inLength)
{
	if (inLength > mLength)
	{
		// Reserve length if needed. Reserve already checks internally if the capacity is already enough.
		Reserve(inLength);

		// Call new operators on new elements.
		for (int i = mLength; i < inLength; i++)
			new (&mData[i]) taType();
	}
	else
	{
		// Call destructors on elements that are being removed. We keep the capacity.
		for (int i = inLength; i < mLength; i++)
			mData[i].~taType();
	}
	mLength = inLength;
}

template<typename taType>
void Array<taType>::Reserve(int inCapacity)
{
	gAssert(inCapacity > 0, "Arrays need to have a capacity of 1 or higher.");

	// Early out if we're already at or above the requested capacity.
	if (inCapacity <= mCapacity)
		return;

	taType* new_data = gStaticCast<taType*>(malloc(inCapacity * sizeof(taType)));
	memset(new_data, 0, inCapacity * sizeof(taType));

	for (int i = 0; i < mLength; i++)
		new_data[i] = gMove(mData[i]);

	free(mData);

	mData = new_data;
}

template<typename taType>
void Array<taType>::ShrinkToFit()
{
	if (mLength == mCapacity)
		return;

	taType* new_data = gStaticCast<taType*>(malloc(mLength * sizeof(taType)));

	for (int i = 0; i < mLength; i++)
		new_data[i] = gMove(mData[i]);

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
		Reserve(mCapacity * 2);

	new (&mData[mLength]) taType(gMove(inValue));
	mLength++;
}

template<typename taType>
template<typename ... taArgs>
void Array<taType>::Emplace(taArgs&&... inArgs)
{
	if (mLength == mCapacity)
		Reserve(mCapacity * 2);

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
		mData[i] = gMove(mData[i + 1]);

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
