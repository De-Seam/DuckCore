#include <DuckCore/Containers/String.h>

// DuckCore includes
#include <DuckCore/Core/Assert.h>

using namespace DC;

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
		if (inChar == character)
			return true;
	return false;
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

String DC::gToString(int inValue)
{
	return std::to_string(inValue);
}

String DC::gToString(uint32 inValue)
{
	return std::to_string(inValue);
}

String DC::gToString(float inValue)
{
	return std::to_string(inValue);
}

String DC::gToString(double inValue)
{
	return std::to_string(inValue);
}
