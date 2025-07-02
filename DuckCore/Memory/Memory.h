#pragma once
#include <DuckCore/Memory/PageAllocator.h>
#include <DuckCore/RTTI/RTTIClass.h>

#include <type_traits>

namespace DC
{
template <typename tType, typename... tArgs>
tType* New(tArgs&&... aArgs);

template <typename tType>
void Delete(tType*& ioPtr);

template<typename tType, typename... tArgs>
requires std::is_base_of_v<RTTIClass, tType>
tType* New(tArgs&&... aArgs)
{
	return PageAllocator<tType>::sNew(std::forward<tArgs>(aArgs)...);
}

template<typename tType, typename ... tArgs>
requires (!std::is_base_of_v<RTTIClass, tType>)
tType* New(tArgs&&... aArgs)
{
	return new tType(std::forward<tArgs>(aArgs)...);
}

template<typename tType>
requires std::is_base_of_v<RTTIClass, tType>
void Delete(tType*& ioPtr)
{
	PageAllocator<tType>::sDelete(ioPtr);
	ioPtr = nullptr;
}

template<typename tType>
requires (!std::is_base_of_v<RTTIClass, tType>)
void Delete(tType*& ioPtr)
{
	delete ioPtr;
	ioPtr = nullptr; 
}
}
