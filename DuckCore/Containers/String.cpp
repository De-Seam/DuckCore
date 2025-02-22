#include <DuckCore/Containers/String.h>

// DuckCore includes
#include <DuckCore/Core/Assert.h>

namespace DC
{
uint64 String::Hash() const
{
	static std::hash<std::string> sHasher;
	return sHasher(mString);
}

String String::sFormatted(const char* inFormat, ...)
{
	va_list args;
	va_start(args, inFormat);

	char buffer[1024];
	int num_chars = vsnprintf(buffer, sizeof(buffer), inFormat, args);
	gAssert(num_chars >= 0 && num_chars <= sizeof(buffer));

	va_end(args);

	return String(buffer);
}

bool String::Contains(char inChar) const
{
	for (const char& character : mString)
	{
		if (inChar == character)
			return true;
	}
	return false;
}

bool String::Contains(const String& aString) const
{
	return mString.find(aString.mString) != std::string::npos;
}

int String::FindFirstCharOccurence(char inChar) const
{
	for (int i = 0; i < Length(); i++)
	{
		const char& character = mString[i];
		if (character == inChar)
			return i;
	}
	return -1;
}

int String::FindLastCharOccurence(char inChar) const
{
	for (int i = Length()-1; i >= 0; i--)
	{
		const char& character = mString[i];
		if (character == inChar)
			return i;
	}
	return -1;
}

Json String::ToJson() const
{
	return mString;
}

void String::FromJson(const Json& inJson)
{
	mString = inJson.get<std::string>();
}

String ToString(int aValue)
{
	return std::to_string(aValue);
}

String ToString(uint32 aValue)
{
	return std::to_string(aValue);
}

String ToString(float aValue)
{
	return std::to_string(aValue);
}

String ToString(double aValue)
{
	return std::to_string(aValue);
}

int IntFromString(const String& aValue)
{
	return std::stoi(aValue.CStr());
}

uint UIntFromString(const String& aValue)
{
	return std::stoul(aValue.CStr());
}

float FloatFromString(const String& aValue)
{
	return std::stof(aValue.CStr());
}

double DoubleFromString(const String& aValue)
{
	return std::stod(aValue.CStr());
}

String GetFileExtension(const String& aPath)
{
	const int dot_pos = aPath.FindLastCharOccurence('.');
	if (dot_pos == -1)
		return "";

	return aPath.SubStr(dot_pos, aPath.Length() - 1);
}

String ToLowerCase(const String& aString)
{
	String result_string = aString;
	for (int i = 0; i < result_string.Length(); i++)
		result_string[i] = (char)tolower(result_string[i]);
	return result_string;
}
}
