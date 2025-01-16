#pragma once
// DuckCore includes
#include <DuckCore/Core/Types.h>

namespace DC
{
class String;

enum class LogLevel : uint8
{
	Info,
	Warning,
	Error
};

void gLog(LogLevel inLevel, const char* inMessage);
void gLog(LogLevel inLevel, const String& inMessage);
void gLog(const DC::String& inMessage);
}