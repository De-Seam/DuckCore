#include <DuckCore/Core/Log.h>

#include <DuckCore/Containers/String.h>

// Std includes
#include <cstdio>
#include <DuckCore/Core/Assert.h>

namespace DC
{
static std::function<void(const RTTI&, ELogLevel, const String&)> sOnLogCallback;

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

	sOnLogCallback(inLogCategoryRTTI, inLevel, inMessage);
}

void gSetOnLogCallback(const std::function<void(const RTTI&, ELogLevel, const String&)>& inOnLogCallback)
{
	gAssert(!sOnLogCallback, "OnLog callback was already set.");
	sOnLogCallback = inOnLogCallback;
}

void gClearOnLogCallback()
{
	sOnLogCallback = {};
}
}
