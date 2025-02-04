#pragma once
// DuckCore includes
#include <functional>
#include <DuckCore/Core/Types.h>
#include <DuckCore/RTTI/RTTIClass.h>

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

// Set the gLog() callback. Only 1 can be set. 
void gSetOnLogCallback(const std::function<void(const RTTI&, ELogLevel, const String&)>& inOnLogCallback);
void gClearOnLogCallback();

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

}
