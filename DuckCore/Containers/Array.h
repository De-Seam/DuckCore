#pragma once
// Core includes
#include <DuckCore/Config.h>

// Std includes
#include <vector>

namespace DC
{

template<typename taType>
class Array
{
public:
	Array() = default;

	taType& operator[](int inIndex) { return At(inIndex); }
	const taType& operator[](int inIndex) const { return At(inIndex); }
	taType& At(int inIndex) { return mArray[inIndex]; }
	const taType& At(int inIndex) const { return mArray[inIndex]; }

	void Resize(int inSize) { mArray.resize(inSize); }
	void Reserve(int inSize) { mArray.reserve(inSize); }
	int Length() const { return static_cast<int>(mArray.size()); }
	bool IsEmpty() const { return Length() == 0; }

	void Clear() { mArray.clear(); }
	void Add(const taType& inValue) { mArray.push_back(std::move(inValue)); }
    void Add(taType&& inValue) { mArray.push_back(std::move(inValue)); }
	template<typename... taArgs>
	void Emplace(taArgs&&... inArgs) { mArray.emplace_back(std::forward<taArgs>(inArgs)...); }

	void PopBack() { mArray.pop_back(); }

	void Remove(int inIndex);
	void SwapRemove(int inIndex) { std::swap(mArray[inIndex], mArray.back()); PopBack(); }
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

	taType& Front() { return mArray.front(); }
	const taType& Front() const { return mArray.front(); }
	taType& Back() { return mArray.back(); }
	const taType& Back() const { return mArray.back(); }

	taType* Data() { return mArray.data(); }
	const taType* Data() const { return mArray.data(); }

	// Custom iterator support
    typename std::vector<taType>::iterator begin() { return mArray.begin(); }
    typename std::vector<taType>::iterator end() { return mArray.end(); }

    typename std::vector<taType>::const_iterator begin() const { return mArray.begin(); }
    typename std::vector<taType>::const_iterator end() const { return mArray.end(); }

    typename std::vector<taType>::const_iterator cbegin() const { return mArray.cbegin(); }
    typename std::vector<taType>::const_iterator cend() const { return mArray.cend(); }

private:
	std::vector<taType> mArray;
};

template<typename taType>
inline void Array<taType>::Remove(int inIndex)
{
	mArray.erase(mArray.begin() + inIndex);
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
