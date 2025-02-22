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
	String(std::string inString) : mString(Move(inString)) {}

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

	void Clear() { mString.clear(); }

	bool IsEmpty() const { return mString.empty(); }

	uint64 Hash() const;

	const char* operator*() const { return mString.c_str(); }
	const char* CStr() const { return mString.c_str(); }

	static String sFormatted(const char* inFormat, ...);

	bool Contains(char inChar) const;
	bool Contains(const String& aString) const;

	String SubStr(int inStart,int inEnd) const { return mString.substr(inStart,inEnd); }
	int FindFirstCharOccurence(char inChar) const; // Find the index of the first time this char appeared in the string, or -1 if none
	int FindLastCharOccurence(char inChar) const; // Find the index of the last time this char appeared in the string, or -1 if none

	int Length() const { return gStaticCast<int>(mString.length()); }

	Json ToJson() const;
	void FromJson(const Json& inJson);

private:
	std::string mString;
};

String ToString(int aValue);
String ToString(uint32 aValue);
String ToString(float aValue);
String ToString(double aValue);

int IntFromString(const String& aValue);
uint UIntFromString(const String& aValue);
float FloatFromString(const String& aValue);
double DoubleFromString(const String& aValue);

template<typename taType>
taType FromString(const String& aValue)
{
	if constexpr (std::is_same_v<taType, int>)
		return IntFromString(aValue);
	else if constexpr (std::is_same_v<taType, uint>)
		return UIntFromString(aValue);
	else if constexpr (std::is_same_v<taType, float>)
		return FloatFromString(aValue);
	else if constexpr (std::is_same_v<taType, double>)
		return DoubleFromString(aValue);
	else
		static_assert(false, "Unsupported type for FromString");
	return {};
}

String GetFileExtension(const String& aPath); // Get the file extension of a path. This is including the dot, so ".png", not "png".
String ToLowerCase(const String& aString);
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