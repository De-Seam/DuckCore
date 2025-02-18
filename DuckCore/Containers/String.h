#pragma once
#include <DuckCore/Config.h>
#include <DuckCore/Core/Types.h>
#include <DuckCore/Utilities/Json.h>
#include <DuckCore/Utilities/Utilities.h>

#include <cstdarg>
#include <string>


namespace DC
{

class String
{
public:
	String() = default;
	String(const char* inString) : mString(inString) {}
	String(const char* inBegin, const char* inEnd) : mString(inBegin, inEnd) {}
	String(std::string inString) : mString(gMove(inString)) {}

	operator const std::string& () const { return mString; }

	bool operator==(const String& inOther) const { return mString == inOther.mString; }

	String operator+(const String& inOther) const { return {mString + inOther.mString}; }
	String operator+(const char* inOther) const { return {mString + inOther}; }
	String operator+(const std::string& inOther) const { return {mString + inOther}; }
	String operator+(const char inChar) const { return {mString + inChar}; }

	template<typename taType>
	String& operator+=(const taType& inOther) { *this = *this + inOther; return *this; }

	char& operator[](int inIndex) { return mString[inIndex]; }
	const char& operator[](int inIndex) const { return mString[inIndex]; }

	bool IsEmpty() const { return mString.empty(); }

	uint64 Hash() const;

	const char* operator*() const { return mString.c_str(); }
	const char* CStr() const { return mString.c_str(); }

	static String sFormatted(const char* inFormat, ...);

	bool Contains(char inChar) const;

	String SubStr(int inStart,int inEnd) const { return mString.substr(inStart,inEnd); }
	int FindFirstCharOccurence(char inChar) const; // Find the index of the first time this char appeared in the string, or -1 if none
	int FindLastCharOccurence(char inChar) const; // Find the index of the last time this char appeared in the string, or -1 if none

	int Length() const { return gStaticCast<int>(mString.length()); }

	Json ToJson() const;
	void FromJson(const Json& inJson);

private:
	std::string mString;
};

String gToString(int inValue);
String gToString(uint32 inValue);
String gToString(float inValue);
String gToString(double inValue);

String gGetFileExtension(const String& aPath); // Get the file extension of a path. This is including the dot, so ".png", not "png".
String gToLowerCase(const String& aString);
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