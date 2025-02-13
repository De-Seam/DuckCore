#include <DuckCore/Core/Log.h>

#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/String.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Threads/ScopedMutex.h>

#include <cstdio>

namespace DC
{
Array<LogEntry> gLogEntries;
Mutex gLogMutex;

static String sGetMessage(ELogLevel inLevel, const String& inMessage)
{
	switch (inLevel)
	{
	case ELogLevel::Info:
		return String("[Info] ") + inMessage;
	case ELogLevel::Warning:
		return String("[Warning] ") + inMessage;
	case ELogLevel::Error:
		return String("[Error] ") + inMessage;
	}
	gAssert(false, "LogLevel not found.");
	return "ERROR could not create log message! Was the LogLevel memory leaded?";
}

void gLog(const RTTI& inLogCategoryRTTI, ELogLevel inLevel, const String& inMessage)
{
	String message = sGetMessage(inLevel, inMessage) + '\n';
	printf(inMessage.CStr());

	LogEntry entry;
	entry.mCategory = &inLogCategoryRTTI;
	entry.mLevel = inLevel;
	entry.mMessage = message;

	ScopedMutexLock lock(gLogMutex);
	gLogEntries.Add(gMove(entry));
}

MutexProtectedPtr<const Array<LogEntry>> gGetLogEntries()
{
	return MutexProtectedPtr<const Array<LogEntry>>(gLogMutex, &gLogEntries);
}
}
