#include <CContainers/String.h>

#include <CUtilities/Assert.hpp>

#include <cstring>

String::String(const char* inCharacters)
{
	SetCharacters(inCharacters, strlen(inCharacters));
}

String::String(const String& inOther)
{
	SetCharacters(inOther.mCharacters, inOther.mLength);
}

String::~String()
{
	Clear();
}

void String::Clear()
{
	if (mCharacters != nullptr)
	{
		delete[] mCharacters;
		mCharacters = nullptr;
	}
	mLength = 0;
	mHash = 0;
}

String& String::operator=(const String& inOther)
{
	Clear();

	SetCharacters(inOther.mCharacters, inOther.mLength);

	return *this;
}

bool String::operator==(const String& inOther) const
{
	bool return_value = mHash == inOther.mHash;
#ifdef _DEBUG
	if (return_value)
		gAssert(strcmp(mCharacters, inOther.mCharacters) == 0);
#endif // _DEBUG
	return mHash == inOther.mHash;
}

void String::SetCharacters(const char* inCharacters, uint32 inLength)
{
	gAssert(mCharacters == nullptr);

	mLength = inLength;
	memcpy(mCharacters, inCharacters, mLength+1);
}
