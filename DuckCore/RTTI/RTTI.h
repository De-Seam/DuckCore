#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Utilities/Json.h>
#include <DuckCore/Utilities/TypeID.h>
#include <DuckCore/Core/Assert.h>

// Std includes
#include <functional>

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
		const char* inBaseClassName,
		std::function<RTTIClass*()> inConstructorFunction
	);

	// We don't want people to copy this class. Just use a pointer or refernece to it
	RTTI& operator=(const RTTI&) = delete;
	RTTI(const RTTI&) = delete;

	bool operator==(const RTTI& inOther) const { return mTypeID == inOther.mTypeID; }

	const char* GetClassName() const { return mClassName; }
	const char* GetBaseClassName() const { return mBaseClassName; }
	RTTIClass* NewInstance() const { return mConstructorFunction(); }

	const RTTITypeID& GetTypeID() const { return mTypeID; }

private:
	const char* mClassName = nullptr;
	const char* mBaseClassName = nullptr;
	std::function<RTTIClass*()> mConstructorFunction;

	RTTITypeID mTypeID;
};

}
