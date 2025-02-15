#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Utilities/TypeID.h>

namespace DC
{

using RTTITypeID = TypeID<class RTTIClass>;

class RTTIClass;

// RTTI are static per RTTI type. They are used to identify the type of a class
class RTTI
{
public:
	RTTI(
		const char* inClassName,
		const RTTI* inBaseClassRTTI
	);

	// We don't want people to copy this class. Just use a pointer or refernece to it
	RTTI& operator=(const RTTI&) = delete;
	RTTI(const RTTI&) = delete;

	bool operator==(const RTTI& inOther) const { return mTypeID == inOther.mTypeID; }

	const char* GetClassName() const { return mClassName; }
	const char* GetBaseClassName() const { return mBaseClassRTTI != nullptr ? mBaseClassRTTI->GetClassName() : "None"; }

	const RTTI* GetBaseClassRTTI() const { return mBaseClassRTTI; }

	const RTTITypeID& GetTypeID() const { return mTypeID; }

private:
	const char* mClassName = nullptr;
	const RTTI* mBaseClassRTTI = nullptr;

	RTTITypeID mTypeID = RTTITypeID::sNew();
};

#define REGISTER_RTTI(inClassName) inClassName::sGetRTTI()

}
