#include <DuckCore/RTTI/RTTI.h>

#include <DuckCore/Containers/Array.h>
#include <DuckCore/Threads/Thread.h>

using namespace DC;

Array<const RTTI*> gRTTIs;

RTTI::RTTI(const char* inClassName, const RTTI* inBaseClassRTTI) :
	mClassName(inClassName),
	mBaseClassRTTI(inBaseClassRTTI)
{
	gRTTIs.Add(this);
}

const RTTI* RTTI::sFindRTTI(const String& aClassName)
{
	const int index = gRTTIs.FindIf([aClassName](const RTTI* aItem) { return aItem->GetClassName() == aClassName; });
	return index != -1 ? gRTTIs[index] : nullptr;
}

const RTTI& RTTI::sGetRTTI(const String& aClassName)
{
	const int index = gRTTIs.FindIf([aClassName](const RTTI* aItem) { return aItem->GetClassName() == aClassName; });
	gAssert(index != -1);
	return *gRTTIs[index];
}
