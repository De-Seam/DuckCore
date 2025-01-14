#pragma once
// Core includes
#include <DuckCore/Core/Types.h>
#include <DuckCore/Utilities/Json.h>

namespace DC
{
class String;

class GUID
{
public:
	GUID() = default;
	GUID(const String& inGUIDString);
	GUID(const char* inGUIDChars);
	GUID(const GUID& inOther) = default;
	GUID(uint64 inGUID) : mGUID(inGUID) {}

	GUID& operator=(const GUID& inOther) = default;

	bool operator==(const GUID& inOther) const { return mGUID == inOther.mGUID; }

	bool IsValid() const { return mGUID != 0; }

	uint64 GetValue() const { return mGUID; }
	operator uint64() const { return mGUID; }

	String ToString() const;
	friend size_t hash_value(const GUID& inGUID) { return inGUID.mGUID; }

	static GUID sCreate();
	static GUID sCombine(const GUID& inA, const GUID& inB, int inSalt = 0);

	static GUID sNone() { return GUID(); }

	virtual Json ToJson() const;
	virtual void FromJson(const Json& inJson);

private:
	uint64 mGUID = 0;
};
}

namespace std
{
	template<typename T>
	struct hash;

	template<>
	struct hash<DC::GUID>
	{
		size_t operator()(const DC::GUID& inUID) const
		{
			return inUID;
		}
	};
}