#pragma once
// Std includes
#include <type_traits>

namespace DC
{
template<typename T>
[[nodiscard]] typename std::remove_reference<T>::type&& Move(T&& aObject) noexcept
{
	// Cast the object to an rvalue reference (T&&)
	return static_cast<typename std::remove_reference<T>::type&&>(aObject);
}

template<typename taType>
void Swap(taType& inA, taType& inB)
{
	taType temp = Move(inA);
	inA = Move(inB);
	inB = Move(temp);
}
}
