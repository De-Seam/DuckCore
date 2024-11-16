#include "RTTI.h"

#include <DuckCore/Utilities/Utilities.h>

using namespace DC;

RTTI::RTTI(const char* inClassName, const char* inBaseClassName) :
	mClassName(inClassName),
	mBaseClassName(inBaseClassName)
{}
