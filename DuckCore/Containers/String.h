#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Core/Assert.h>
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
	int num_chars = vsnprintf(buffer, sizeof(buffer), inFormat, args);
    gAssert(num_chars >= 0 && num_chars <= sizeof(buffer));

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