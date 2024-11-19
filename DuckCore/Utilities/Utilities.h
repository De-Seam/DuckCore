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
}
