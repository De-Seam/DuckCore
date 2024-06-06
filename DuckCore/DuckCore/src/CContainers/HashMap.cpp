#include "CContainers/HashMap.h"

template<typename taKeyType, typename taValueType>
HashMap<taKeyType, taValueType>::~HashMap()
{
	for (uint64 i = 0; i < mCapacity; i++)
	{
		HashNode& data_entry = mData[i];
		if (data_entry.mHash != 0)
			~data_entry();
	}

	free(mData);
}

template<typename taKeyType, typename taValueType>
taValueType* HashMap<taKeyType, taValueType>::Find(const taKeyType& inKey)
{
	uint64 hash = gHash(inKey);
	uint32 index = hash % mCapacity;
	HashNode& entry = mData[index];

	while (entry.mHash != 0)
	{
		if (entry.mHash == hash)
		{
			gAssert(entry.mKey == inKey && "Hash Collision");
			return &entry.mValue;
		}
		if (entry.mNext == nullptr)
			break;

		entry = *entry.mNext;
	}

	return nullptr;
}

template<typename taKeyType, typename taValueType>
void HashMap<taKeyType, taValueType>::Add(const taKeyType& inKey, const taValueType& inValue)
{
	uint64 hash = gHash(inKey);
	uint32 index = hash % mCapacity;
	DataEntry& entry = mData[index];
	while (entry.mHash != 0)
	{
		if (entry.mNext == nullptr)
			entry.mNext = new HashNode;
		entry = *entry.mNext;
	}

	entry.mKey = inKey;
	entry.mHash = hash;
	entry.mValue = inValue;
}

template<typename taKeyType, typename taValueType>
void HashMap<taKeyType, taValueType>::Expand()
{
	Resize(mCapacity * 2);
}

template<typename taKeyType, typename taValueType>
void HashMap<taKeyType, taValueType>::Resize(uint32 inNewCapacity)
{
	// Create new data array
	HashNode* new_data = new HashNode[inNewCapacity];

	// Copy old data to new data
	for (uint32 i = 0; i < mCapacity; i++)
	{
		HashNode& entry = mData[i];
		if (entry.mHash == 0)
			continue;

		uint32 new_index = entry.mHash % inNewCapacity;
		new_data[new_index] = entry;
		new_data[new_index].mNext = nullptr;

		if (!mData[i].mOccupied)
		{
			uint32 new_index = mData[i].mHash % inNewCapacity;
			while (new_data[new_index].mKey != 0)
			{
				new_index = (new_index + 1) % inNewCapacity;
			}
			new_data[new_index] = mData[i];
		}
	}

	// Delete old data
	delete[] mData;

	// Set new data
	mData = new_data;
	mCapacity = inNewCapacity;
}
