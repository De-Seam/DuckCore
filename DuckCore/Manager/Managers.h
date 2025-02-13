#pragma once
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/UniquePtr.h>
#include <DuckCore/Manager/Manager.h>

namespace DC
{
class Managers
{
public:
	template<typename taManagerType>
	static void sAdd(UniquePtr<taManagerType> inManager);

	template<typename taManagerType>
	static taManagerType& sGet();

	template<typename taManagerType>
	static taManagerType* sFind();

private:
	Managers() = default;

	inline static HashMap<const RTTI*, UniquePtr<Manager>> sManagers;
};

template<typename taManagerType>
void Managers::sAdd(UniquePtr<taManagerType> inManager) 
{
	const RTTI* rtti = &taManagerType::sGetRTTI();
	gAssert(!sManagers.Contains(rtti));

	sManagers[rtti] = gMove(inManager);
}

template<typename taManagerType>
taManagerType& Managers::sGet() 
{
	const RTTI* rtti = &taManagerType::sGetRTTI();
	gAssert(sManagers.Contains(rtti));

	return *gStaticCast<taManagerType*>(sManagers.At(rtti).Get());
}

template<typename taManagerType>
taManagerType* Managers::sFind() 
{
	const RTTI* rtti = &taManagerType::sGetRTTI();
	return *sManagers.Find(rtti);
}
}
