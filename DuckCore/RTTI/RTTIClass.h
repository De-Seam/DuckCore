#pragma once
#include "RTTI.h"

namespace DC
{
class RTTIClass
{
public:
	virtual ~RTTIClass() = default;

	virtual const RTTI& GetRTTI() const { return sRTTI; }
	static const RTTI& sGetRTTI() { return sRTTI; }
	static RTTIClass* sNewInstance() { return new RTTIClass; }

	template<typename taType>
	bool IsA() const;
	virtual bool IsARTTI(const RTTI& inRTTI) const;

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
	return IsARTTI(taType::sGetRTTI());
}

template<typename taType>
taType* RTTIClass::As() 
{
	if (this->IsARTTI(taType::sGetRTTI()))
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
}

#define RTTI_CLASS_DECLARATION_BASE(inClassName, inBaseClassName) \
private: \
	using Base = inBaseClassName; \
\
public: \
	virtual const DC::RTTI& GetRTTI() const override { return sRTTI; } \
	static const DC::RTTI& sGetRTTI() { return sRTTI; } \
	virtual bool IsARTTI(const DC::RTTI& inRTTI) const \
	{ \
		if (sGetRTTI().GetTypeID() == inRTTI.GetTypeID()) \
			return true; \
		return Base::IsARTTI(inRTTI); \
	} \
private: \
	inline static DC::RTTI sRTTI = DC::RTTI( \
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