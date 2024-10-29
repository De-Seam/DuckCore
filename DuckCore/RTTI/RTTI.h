#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Utilities/Json.h>
#include <DuckCore/Utilities/TypeID.h>
#include <DuckCore/Core/Assert.h>

// Std includes
#include <functional>

namespace DC
{

using RTTITypeID = TypeID<class RTTIClass>;

class RTTIClass;

// RTTI are static per RTTI type. They are used to identify the type of a class
class RTTI
{
public:
	RTTI(
		const char* inClassName,
		const char* inBaseClassName,
		std::function<RTTIClass*()> inConstructorFunction
	);

	// We don't want people to copy this class. Just use a pointer or refernece to it
	RTTI& operator=(const RTTI&) = delete;
	RTTI(const RTTI&) = delete;

	bool operator==(const RTTI& inOther) const { return mTypeID == inOther.mTypeID; }

	const char* GetClassName() const { return mClassName; }
	const char* GetBaseClassName() const { return mBaseClassName; }
	RTTIClass* NewInstance() const { return mConstructorFunction(); }

	const RTTITypeID& GetTypeID() const { return mTypeID; }

private:
	const char* mClassName = nullptr;
	const char* mBaseClassName = nullptr;
	std::function<RTTIClass*()> mConstructorFunction;

	RTTITypeID mTypeID;
};

class RTTIClass
{
public:
	virtual ~RTTIClass() = default;

	virtual const RTTI& GetRTTI() const { return sRTTI; }
	static const RTTI& sGetRTTI() { return sRTTI; }
	static RTTIClass* sNewInstance() { return new RTTIClass; }

	template<typename taType>
	bool IsA() const;
	virtual bool IsA(const RTTI& inRTTI) const;

	template<typename taType>
	taType* As();

	virtual Json Serialize() const;
	virtual void Deserialize(const Json& inJson);

private:
	inline static RTTI sRTTI = RTTI(
		"RTTIClass", // Class Name
		"NONE", // Base Class Name
		[]() { return reinterpret_cast<RTTIClass*>(sNewInstance()); }
	);
};

template<typename taType>
bool RTTIClass::IsA() const 
{
	return IsA(taType::sGetRTTI());
}

template<typename taType>
taType* RTTIClass::As() 
{
	if (this->IsA(taType::sGetRTTI()))
		return static_cast<taType*>(this);
	return nullptr;
}

// Template function for to_json
template<typename T>
typename std::enable_if<has_serialize<T, Json()>::value>::type
to_json(Json& j, const T& obj) 
{
	j = obj.Serialize();
}

// Template function for from_json
template<typename T>
typename std::enable_if<has_deserialize<T, void(const Json&)>::value>::type
from_json(const Json& j, T& obj) 
{
	obj.Deserialize(j);
}

template<typename T>
typename std::enable_if<has_serialize<T, Json()>::value>::type
to_json(Json& j, const T* obj) 
{
	j = obj->Serialize();
}

// Template function for from_json
template<typename T>
typename std::enable_if<has_deserialize<T, void(const Json&)>::value>::type
from_json(const Json& j, T* obj) 
{
	obj->Deserialize(j);
}

#define RTTI_CLASS_DECLARATION_BASE(inClassName, inBaseClassName) \
private: \
	using Base = inBaseClassName; \
\
public: \
	virtual const RTTI& GetRTTI() const override { return sRTTI; } \
	static const RTTI& sGetRTTI() { return sRTTI; } \
	virtual bool IsA(const RTTI& inRTTI) const \
	{ \
		if (sGetRTTI().GetTypeID() == inRTTI.GetTypeID()) \
			return true; \
		return Base::IsA(inRTTI); \
	} \
private: \
	inline static RTTI sRTTI = RTTI( \
		#inClassName, \
		#inBaseClassName, \
		[]() { return reinterpret_cast<RTTIClass*>(sNewInstance()); } \
	);

#define RTTI_VIRTUAL_CLASS(inClassName, inBaseClassName) \
public: \
	static inClassName* sNewInstance() { gAssert(false); return nullptr; } \
RTTI_CLASS_DECLARATION_BASE(inClassName, inBaseClassName) 

#define RTTI_CLASS(inClassName, inBaseClassName) \
public: \
	static inClassName* sNewInstance() { return new inClassName; } \
RTTI_CLASS_DECLARATION_BASE(inClassName, inBaseClassName) 

}
