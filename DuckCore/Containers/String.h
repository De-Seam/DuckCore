#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Core/Types.h>

// Std includes
#include <cstdarg>
#include <string>

namespace DC
{

class String
{
public:
	String() = default;
	String(const char* inString) : mString(inString) {}
	String(const std::string& inString) : mString(inString) {}

	operator std::string&() { return mString; }
	operator const std::string& () const { return mString; }

	bool operator==(const String& inOther) const { return mString == inOther.mString; }

	uint64 Hash() const;

	const char* operator*() const { return mString.c_str(); }
	const char* CStr() const { return mString.c_str(); }

	static String sFormatted(const char* inFormat, ...);

private:
	std::string mString;
};

inline String String::sFormatted(const char* inFormat, ...)
{
	va_list args;
	va_start(args, inFormat);

	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), inFormat, args);

	va_end(args);

	return String(buffer);
}

}

namespace std
{
	template<typename T>
	struct hash;

	template<>
	struct hash<DC::String>
	{
		size_t operator()(const DC::String& inString) const
		{
			return inString.Hash();
		}
	};
}