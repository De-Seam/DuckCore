#pragma once
#include <CContainers/Pair.h>
#include <CCore/Types.h>

template<typename taKeyType, typename taValueType>
class HashMap
{
public:
	~HashMap();

	taValueType* Find(const taKeyType& inKey);

	void Add(const taKeyType& inKey, const taValueType& inValue);

private:
	void Expand();
	void Resize(uint32 inNewSize);

	uint32 mCapacity = 0;

	struct DataEntry
	{
		bool mOccupied = false;
		taKeyType mKey;
		uint64 mHash;
		taValueType mValue;
	};

	DataEntry* mData = nullptr;
};
