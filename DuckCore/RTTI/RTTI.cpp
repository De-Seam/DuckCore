#include <DuckCore/RTTI/RTTI.h>

#include <DuckCore/RTTI/RTTIRegistry.h>

using namespace DC;

RTTI::RTTI(const char* inClassName, const char* inBaseClassName) :
	mClassName(inClassName),
	mBaseClassName(inBaseClassName)
{
	gRTTIRegistry.RegisterRTTI(*this);
}
