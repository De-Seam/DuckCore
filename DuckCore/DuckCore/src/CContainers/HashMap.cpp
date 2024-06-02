#include "CContainers/HashMap.h"

template<typename taKeyType, typename taValueType>
HashMap<taKeyType, taValueType>::~HashMap()
{
	for (uint64 i = 0; i < mCapacity; i++)
	{
		DataEntry& data_entry = mData[i];
		if (data_entry.mCountFromWantedIndex != -1)
			~data_entry();
	}

	free(mData);
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
	for (uint32 i = 0; i < mSize; i++)
	{
		if (mData[i].mKey != 0)
		{
			uint32 new_index = mData[i].mData.mFirst % inNewSize;
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
	mSize = inNewSize;
}
