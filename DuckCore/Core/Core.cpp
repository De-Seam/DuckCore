#include <DuckCore/Core/Core.h>

#include <DuckCore/Manager/Manager.h>
#include <DuckCore/RTTI/RTTI.h>
#include <DuckCore/RTTI/RTTIRefClass.h>

namespace DC
{
void RegisterCoreRTTI()
{
	REGISTER_RTTI(RTTIClass);
	REGISTER_RTTI(RTTIRefClass);
	REGISTER_RTTI(Manager);
}
}
