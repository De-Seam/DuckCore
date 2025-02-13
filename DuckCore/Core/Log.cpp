#include <DuckCore/Core/Log.h>

#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/String.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Core/LogManager.h>
#include <DuckCore/Manager/Managers.h>
#include <DuckCore/Threads/ScopedMutex.h>

#include <cstdio>

namespace DC
{
void gLogInternal(const RTTI& inLogCategoryRTTI, ELogLevel inLevel, const char* inMessage)
{
	Managers::sGet<LogManager>().Log(inLogCategoryRTTI, inLevel, inMessage);
}

void gLog(const char* inMessage)
{
	gLog<LogCategoryDefault>(ELogLevel::Info, inMessage);
}

void gLog(ELogLevel inLevel, const char* inMessage)
{
	gLog<LogCategoryDefault>(inLevel, inMessage);
}
}
