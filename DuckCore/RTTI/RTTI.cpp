#include <DuckCore/RTTI/RTTI.h>

#include <DuckCore/RTTI/RTTIRegistry.h>

using namespace DC;

RTTI::RTTI(const char* inClassName, const RTTI* inBaseClassRTTI) :
	mClassName(inClassName),
	mBaseClassRTTI(inBaseClassRTTI)
{
	gRTTIRegistry.RegisterRTTI(*this);
}
