#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Core/Types.h>

// Std includes
#include <cstdarg>
#include <string>

#include <DuckCore/Utilities/Json.h>

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

	String operator+(const String& inOther) const { return {mString + inOther.mString}; }
	String operator+(const char* inOther) const { return {mString + inOther}; }
	String operator+(const std::string& inOther) const { return {mString + inOther}; }

	template<typename taType>
	String& operator+=(const taType& inOther) { *this = *this + inOther; return *this; }

	uint64 Hash() const;

	const char* operator*() const { return mString.c_str(); }
	const char* CStr() const { return mString.c_str(); }

	static String sFormatted(const char* inFormat, ...);

	String SubStr(int inStart,int inEnd) const { return mString.substr(inStart,inEnd); }

	int Length() const { return mString.length(); }

	virtual Json Serialize() const;
	virtual void Deserialize(const Json& inJson);

private:
	std::string mString;
};

String gToString(int inValue);
String gToString(uint32 inValue);
String gToString(float inValue);
String gToString(double inValue);

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