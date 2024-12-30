#include <DuckCore/Core/Log.h>

// DuckCore includes
#include <DuckCore/Containers/String.h>

// Std includes
#include <cstdio>

namespace DC
{
void gLog(LogLevel inLevel, const String& inMessage)
{
	printf(inMessage.CStr());
	printf("\n");
}

void gLog(const String& inMessage)
{
	printf(inMessage.CStr());
	printf("\n");
}
}
