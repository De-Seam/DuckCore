#include "CContainers/HashMap.h"

template<typename taKeyType, typename taValueType>
HashMap<taKeyType, taValueType>::~HashMap()
{
	for (uint64 i = 0; i < mCapacity; i++)
	{
		DataEntry& data_entry = mData[i];
		if (data_entry.mOccupied)
			~data_entry();
	}

	free(mData);
}

template<typename taKeyType, typename taValueType>
taValueType* HashMap<taKeyType, taValueType>::Find(const taKeyType& inKey)
{
	uint64 hash = gHash(inKey);
	uint32 initial_index = hash % mCapacity;
	uint32 index = initial_index;
	DataEntry& entry = mData[index];
	while (entry.mOccupied && entry.mHash != hash && entry.mHash % mCapacity == initial_index)
	{
		index = (index + 1) % mCapacity;
		if (index >= mCapacity)
			return nullptr;
		entry = mData[index];
	}

	if (mData[index].first == inKey)
	{
		return &entry.mValue;
	}
	else
	{
		return nullptr;
	}
}

template<typename taKeyType, typename taValueType>
void HashMap<taKeyType, taValueType>::Add(const taKeyType& inKey, const taValueType& inValue)
{
	uint64 hash = gHash(inKey);
	uint32 initial_index = hash % mCapacity;
	uint32 index = initial_index;
	DataEntry& entry = mData[index];
	while (entry.mOccupied && entry.mHash != hash && entry.mHash % mCapacity == initial_index)
	{
		index = (index + 1) % mCapacity;
		entry = mData[index];
	}

	entry.mOccupied = true;
	entry.mHash = hash;
	entry.mKey = inKey;
	entry.mValue = inValue;
}

template<typename taKeyType, typename taValueType>
void HashMap<taKeyType, taValueType>::Expand()
{
	Resize(mCapacity * 2);
}

template<typename taKeyType, typename taValueType>
void HashMap<taKeyType, taValueType>::Resize(uint32 inNewSize)
{
	// Create new data array
	DataEntry* new_data = new DataEntry[inNewSize];

	// Copy old data to new data
	for (uint32 i = 0; i < mCapacity; i++)
	{
		if (!mData[i].mOccupied)
		{
			uint32 new_index = mData[i].mHash % inNewSize;
			while (new_data[new_index].mKey != 0)
			{
				new_index = (new_index + 1) % inNewSize;
			}
			new_data[new_index] = mData[i];
		}
	}

	// Delete old data
	delete[] mData;

	// Set new data
	mData = new_data;
	mCapacity = inNewSize;
}
