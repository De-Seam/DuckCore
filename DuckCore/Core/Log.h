#pragma once
// DuckCore includes
#include <functional>

#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/String.h>
#include <DuckCore/Core/Types.h>
#include <DuckCore/Manager/Manager.h>
#include <DuckCore/RTTI/RTTIClass.h>
#include <DuckCore/Threads/MutexProtectedPtr.h>

namespace DC
{
class String;

enum class ELogLevel : uint8
{
	Info,
	Warning,
	Error
};

class LogCategory : public RTTIClass
{
	RTTI_CLASS(LogCategory, RTTIClass)
};

class LogCategoryDefault final : public LogCategory
{
	RTTI_CLASS(LogCategoryDefault, LogCategory)
};

template<typename taCategory>
inline void gLog(ELogLevel inLevel, const char* inMessage);
template<typename taCategory>
inline void gLog(ELogLevel inLevel, const String& inMessage);

// Log helper function. Quickly logs something to the default category with ELogLevel::Info
inline void gLog(const String& inMessage);

// Internal log function
void gLog(const RTTI& inLogCategoryRTTI, ELogLevel inLevel, const String& inMessage);

template <typename taCategory>
void gLog(ELogLevel inLevel, const char* inMessage)
{
	gLog(taCategory::sGetRTTI(), inLevel, inMessage);
}


template <typename taCategory>
inline void gLog(ELogLevel inLevel, const String& inMessage)
{
	gLog(taCategory::sGetRTTI(), inLevel, inMessage);
}

inline void gLog(const String& inMessage)
{
	gLog<LogCategoryDefault>(ELogLevel::Info, inMessage);
}

struct LogEntry
{
	const RTTI* mCategory;
	ELogLevel mLevel;
	String mMessage;
};

MutexProtectedPtr<const Array<LogEntry>> gGetLogEntries();
}
