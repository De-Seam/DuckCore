#pragma once
// Core includes
#include <DuckCore/Core/Types.h>
#include <DuckCore/Threads/Atomic.h>

#define STATIC_TYPE_ID_NO_VIRTUAL(inName) \
public: \
	static const inName##TypeID& sGet##inName##TypeID() { return s##inName##TypeID; }; \
\
private: \
	inline static inName##TypeID s##inName##TypeID = {}; \
public:

#define STATIC_TYPE_ID(inName) \
STATIC_TYPE_ID_NO_VIRTUAL(inName) \
	virtual const inName##TypeID& Get##inName##TypeID() const { return s##inName##TypeID; } 

namespace DC
{

// TypeID increments by 1 each time it's instantiated
// taType for the base type
template<typename taType>
class TypeID
{
public:
	TypeID(const TypeID& inOther) : mID(inOther.mID) {}

	bool operator==(const TypeID& inOther) const { return mID == inOther.mID; }

	friend size_t hash_value(const TypeID& inTypeID) { return inTypeID.Get(); }

	int16 Get() const { return mID; }
	operator int16() const { return mID; }

	static TypeID<taType> sNew() { return TypeID<taType>(); }

private:
	TypeID();

	int16 mID = -1;

	static inline Atomic<int16> sNextID = 0; 
};

template<typename taType>
inline TypeID<taType>::TypeID()
{
	mID = sNextID++;
}

}

namespace std
{
	template <typename T> struct hash;

	template<typename taType>
	struct hash<DC::TypeID<taType>>
	{
		size_t operator()(const DC::TypeID<taType>& inTypeID) const
		{
			return static_cast<size_t>(inTypeID);
		}
	};

}