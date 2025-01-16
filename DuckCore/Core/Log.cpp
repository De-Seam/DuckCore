#include <DuckCore/Core/Log.h>

#include <DuckCore/Containers/String.h>

// Std includes
#include <cstdio>

namespace DC
{
void gLog(LogLevel inLevel, const char* inMessage)
{
	gLog(inLevel, String(inMessage));
}

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
