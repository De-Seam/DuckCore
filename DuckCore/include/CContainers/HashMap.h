#pragma once
#include <CContainers/Array.h>
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
	void Resize(uint32 inNewCapacity);

	uint32 mCapacity = 0;

	struct HashNode
	{
		HashNode* mNext = nullptr;
		taKeyType mKey;
		uint64 mHash = 0; ///< 0 means empty
		taValueType mValue;
	};

	HashNode* mData = nullptr;
};
