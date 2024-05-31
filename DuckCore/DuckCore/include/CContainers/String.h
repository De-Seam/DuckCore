#pragma once
#include <CCore/Types.hpp>

class String
{
public:
	String() = default;
	String(const char* inCharacters);
	String(const String& inOther);
	~String();

	void Clear();
	uint32 Length() const { return mLength; }

	const char* operator*() const { return mCharacters; }

	String& operator=(const String& inOther);
	bool operator==(const String& inOther) const;
	bool operator!=(const String& inOther) const { return !(*this == inOther); }

private:
	void SetCharacters(const char* inCharacters, uint32 inLength);

	char* mCharacters;
	uint32 mLength;
	uint64 mHash;
};