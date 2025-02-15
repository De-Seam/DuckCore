#pragma once
#include <DuckCore/RTTI/RTTI.h>

namespace DC
{
class RTTIClass
{
public:
	virtual ~RTTIClass() = default;

	virtual const RTTI& GetRTTI() const { return sRTTI; }
	virtual RTTI& GetRTTI() { return sRTTI; }
	static RTTI& sGetRTTI() { return sRTTI; }
	static RTTIClass* sNewInstance() { return new RTTIClass; }

	template<typename taType>
	bool IsA() const;
	virtual bool IsARTTI(const RTTI& inRTTI) const;

	template<typename taType>
	taType* As();

	template<typename taType>
	taType& Cast();

private:
	inline static RTTI sRTTI = RTTI(
		"RTTIClass", // Class Name
		nullptr // Base Class RTTI
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

template <typename taType>
taType& RTTIClass::Cast()
{
	gAssert(this->IsARTTI(taType::sGetRTTI()) && "Invalid cast!");
	return *gStaticCast<taType*>(this);
}

}

#define RTTI_CLASS_DECLARATION_BASE(inClassName, inBaseClassName) \
private: \
	using Base = inBaseClassName; \
\
public: \
	virtual const DC::RTTI& GetRTTI() const override { return sRTTI; } \
	virtual DC::RTTI& GetRTTI() override { return sRTTI; } \
	static DC::RTTI& sGetRTTI() { return sRTTI; } \
	virtual bool IsARTTI(const DC::RTTI& inRTTI) const \
	{ \
		if (sGetRTTI().GetTypeID() == inRTTI.GetTypeID()) \
			return true; \
		return Base::IsARTTI(inRTTI); \
	} \
private: \
	inline static DC::RTTI sRTTI = DC::RTTI( \
		#inClassName, \
		&inBaseClassName::sGetRTTI() \
	);

#define RTTI_CLASS(inClassName, inBaseClassName) \
RTTI_CLASS_DECLARATION_BASE(inClassName, inBaseClassName)