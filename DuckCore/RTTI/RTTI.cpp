#include <DuckCore/RTTI/RTTI.h>

using namespace DC;

RTTI::RTTI(const char* inClassName, const RTTI* inBaseClassRTTI) :
	mClassName(inClassName),
	mBaseClassRTTI(inBaseClassRTTI)
{}
