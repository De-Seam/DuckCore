#pragma once
#include <CContainers/Pair.h>
#include <CCore/Types.h>

template<typename taKeyType, typename taValueType>
class HashMap
{
public:
	~HashMap();

	void Add(const taKeyType& inKey, const taValueType& inValue)
	{
		if (mSize == mCapacity)
		{
			Expand();
		}

		uint64 hash = gHash(inKey);
		uint32 index = hash % mCapacity;
		while (mData[index].first != inKey && mData[index].first != taKeyType())
		{
			index = (index + 1) % mCapacity;
		}

		mData[index] = {hash, inValue};
		mSize++;
	}

private:
	void Expand();
	void Resize(uint32 inNewSize);

	uint32 mSize = 0;
	uint32 mCapacity = 0;

	struct DataEntry
	{
		int32 mCountFromWantedIndex = -1; ///< -1 if invalid, free data entry
		Pair<uint64, taValueType> mData;
	};

	DataEntry* mData = nullptr;
};
