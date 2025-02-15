#pragma once
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/UniquePtr.h>
#include <DuckCore/Manager/Manager.h>

namespace DC
{
class Managers
{
public:
	Managers() = delete;

	template<typename taManagerType>
	static void sAdd(UniquePtr<taManagerType> inManager);

	template<typename taManagerType>
	static taManagerType& sGet();

	template<typename taManagerType>
	static taManagerType* sFind();

private:
	static Array<UniquePtr<Manager>> sManagers; // Array of managers. The index is the type id of the manager.
};

template<typename taManagerType>
void Managers::sAdd(UniquePtr<taManagerType> inManager) 
{
	static_assert(std::is_base_of_v<Manager, taManagerType>);
	static_assert(true == std::is_member_pointer<decltype(&taManagerType::value)>::sTypeID, "Manager needs to have MANAGER_BASE_CLASS()");

	TypeID<Manager> type_id = taManagerType::sManagerTypeID;

	sManagers.Resize(gMax(sManagers.Length(), gStaticCast<int>(type_id)));
	gAssert(sManagers[type_id] == nullptr, "Manager was already added.");
	sManagers[type_id] = gMove(inManager);
}

template<typename taManagerType>
taManagerType& Managers::sGet() 
{
	static_assert(std::is_base_of_v<Manager, taManagerType>);
	static_assert(true == std::is_member_pointer<decltype(&taManagerType::value)>::sTypeID, "Manager needs to have MANAGER_BASE_CLASS()");

	TypeID<Manager> type_id = taManagerType::sManagerTypeID;
	gAssert(sManagers[type_id] != nullptr, "Manager was not added.");
	return *sManagers[type_id];
}

template<typename taManagerType>
taManagerType* Managers::sFind() 
{
	static_assert(std::is_base_of_v<Manager, taManagerType>);
	static_assert(true == std::is_member_pointer<decltype(&taManagerType::value)>::sTypeID, "Manager needs to have MANAGER_BASE_CLASS()");

	TypeID<Manager> type_id = taManagerType::sManagerTypeID;

	if (!sManagers.IsValidIndex(type_id))
		return nullptr;

	return *sManagers[type_id];
}
}
