#include "RTTI.h"

#include <DuckCore/Utilities/Utilities.h>

using namespace DC;

RTTI::RTTI(const char* inClassName, const char* inBaseClassName, const std::optional<std::function<RTTIClass*()>>& inConstructorFunction) :
	mClassName(inClassName),
	mBaseClassName(inBaseClassName),
	mConstructorFunction(inConstructorFunction),
{}
