#pragma once
// DuckCore includes
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/String.h>
#include <DuckCore/Core/Types.h>
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

// Internal log function
void LogInternal(const RTTI& aLogCategoryRTTI, ELogLevel aLevel, const char* aMessage);

template<typename taCategory>
void Log(ELogLevel aLevel, const char* aMessage) { LogInternal(taCategory::sGetRTTI(), aLevel, aMessage); }
void Log(ELogLevel aLevel, const char* aMessage); // Log helper function. Quickly logs something to the default category.
void Log(const char* aMessage); // Log helper function. Quickly logs something to the default category with ELogLevel::Info.

template<typename taCategory>
void Log(ELogLevel aLevel, const String& aMessage) { LogInternal(taCategory::sGetRTTI(), aLevel, *aMessage); }
inline void Log(ELogLevel aLevel, const String& aMessage) { Log(aLevel, *aMessage); } // Log helper function. Quickly logs something to the default category.
inline void Log(const String& aMessage) { Log(*aMessage); }; // Log helper function. Quickly logs something to the default category with ELogLevel::Info.

struct LogEntry
{
	const RTTI* mCategory;
	ELogLevel mLevel;
	String mMessage;
};

MutexProtectedPtr<const Array<LogEntry>> GetLogArray(); // (Async) returns the array of log entries.

}
