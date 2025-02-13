#pragma once
// DuckCore includes
#include <DuckCore/Containers/String.h>
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

// Internal log function
void gLogInternal(const RTTI& inLogCategoryRTTI, ELogLevel inLevel, const char* inMessage);

template<typename taCategory>
void gLog(ELogLevel inLevel, const char* inMessage) { gLogInternal(taCategory::sGetRTTI(), inLevel, inMessage); }
void gLog(ELogLevel inLevel, const char* inMessage); // Log helper function. Quickly logs something to the default category.
void gLog(const char* inMessage); // Log helper function. Quickly logs something to the default category with ELogLevel::Info.

template<typename taCategory>
void gLog(ELogLevel inLevel, const String& inMessage) { gLogInternal(taCategory::sGetRTTI(), inLevel, *inMessage); }
inline void gLog(ELogLevel inLevel, const String& inMessage) { gLog(inLevel, *inMessage); } // Log helper function. Quickly logs something to the default category.
inline void gLog(const String& inMessage) { gLog(*inMessage); }; // Log helper function. Quickly logs something to the default category with ELogLevel::Info.

}
