#pragma once
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/UniquePtr.h>
#include <DuckCore/Managers/Manager.h>

namespace DC
{
class Managers
{
public:
	Managers() = delete;

	template<typename taManagerType>
	static void sAdd(taManagerType* aManager);

	template<typename taManagerType>
	static taManagerType& sGet();

	template<typename taManagerType>
	static taManagerType* sFind();

private:
	inline static Array<Manager*> sManagers; // Array of managers. The index is the type id of the manager.
};

template<typename taType> requires std::is_base_of_v<Manager, taType>
taType& Get() { return Managers::sGet<taType>(); }

template <typename T, typename = void>
struct has_myVar : std::false_type {};

template <typename T>
struct has_myVar<T, std::void_t<decltype(T::sManagerTypeID)>> : std::true_type {};

template <typename T>
constexpr bool has_myVar_v = has_myVar<T>::value;

template<typename taManagerType>
void Managers::sAdd(taManagerType* aManager) 
{
	static_assert(std::is_base_of_v<Manager, taManagerType>);
	static_assert(has_myVar_v<taManagerType>, "Manager needs to have MANAGER_BASE_CLASS()");

	TypeID<Manager> type_id = taManagerType::sManagerTypeID;

	int length = sManagers.Length();
	int next = Max(length, gStaticCast<int>(type_id) + 1);
	int size = Max(length, next);
	sManagers.Resize(size);
	gAssert(sManagers[type_id] == nullptr, "Manager was already added.");
	sManagers[type_id] = aManager;
}

template<typename taManagerType>
taManagerType& Managers::sGet() 
{
	static_assert(std::is_base_of_v<Manager, taManagerType>);
	static_assert(has_myVar_v<taManagerType>, "Manager needs to have MANAGER_BASE_CLASS()");

	TypeID<Manager> type_id = taManagerType::sManagerTypeID;
	gAssert(sManagers.IsValidIndex(type_id), "Manager was not added.");

	Manager* manager = sManagers[type_id];
	gAssert(manager != nullptr, "Manager was not added.");

	return manager->Cast<taManagerType>();
}

template<typename taManagerType>
taManagerType* Managers::sFind() 
{
	static_assert(std::is_base_of_v<Manager, taManagerType>);
	static_assert(has_myVar_v<taManagerType>, "Manager needs to have MANAGER_BASE_CLASS()");

	// Manager needs to have MANAGER_BASE_CLASS().
	TypeID<Manager> type_id = taManagerType::sManagerTypeID;

	if (!sManagers.IsValidIndex(type_id))
		return nullptr;

	Manager* manager = sManagers[type_id];
	return gStaticCast<taManagerType*>(manager);
}
}
