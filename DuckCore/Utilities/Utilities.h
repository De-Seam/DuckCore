#pragma once
// Std includes
#include <type_traits>

namespace DC
{
template<typename T>
[[nodiscard]] typename std::remove_reference<T>::type&& gMove(T&& inObject) noexcept
{
	// Cast the object to an rvalue reference (T&&)
	return static_cast<typename std::remove_reference<T>::type&&>(inObject);
}

template<typename taType>
void gSwap(taType& inA, taType& inB)
{
	taType temp = gMove(inA);
	inA = gMove(inB);
	inB = gMove(temp);
}
}
