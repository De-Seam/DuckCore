#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Utilities/Json.h>
#include <DuckCore/Utilities/TypeID.h>

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
		const std::optional<std::function<RTTIClass*()>>& inConstructorFunction = std::nullopt
	);

	// We don't want people to copy this class. Just use a pointer or refernece to it
	RTTI& operator=(const RTTI&) = delete;
	RTTI(const RTTI&) = delete;

	bool operator==(const RTTI& inOther) const { return mTypeID == inOther.mTypeID; }

	const char* GetClassName() const { return mClassName; }
	const char* GetBaseClassName() const { return mBaseClassName; }
	bool IsNewInstanceAllowed() const { return mConstructorFunction.has_value(); }
	RTTIClass* NewInstance() const { gAssert(mConstructorFunction.has_value()); const std::function<RTTIClass*()>& function = mConstructorFunction.value(); return function(); }

	const RTTITypeID& GetTypeID() const { return mTypeID; }

private:
	const char* mClassName = nullptr;
	const char* mBaseClassName = nullptr;
	std::optional<std::function<RTTIClass*()>> mConstructorFunction;

	RTTITypeID mTypeID;
};

}
