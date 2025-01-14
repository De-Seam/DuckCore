#include <DuckCore/Core/Core.h>
#include <DuckCore/RTTI/RTTI.h>
#include <DuckCore/RTTI/RTTIRefClass.h>

namespace DC
{
void gRegisterCoreRTTI()
{
	REGISTER_RTTI(RTTIClass);
	REGISTER_RTTI(RTTIRefClass);
}
}
