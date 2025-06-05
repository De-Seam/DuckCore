#pragma once
#include <DuckCore/Containers/StaticArray.h>
#include <DuckCore/Core/Types.h>

#include <type_traits>

namespace DC
{

// Check if a type tType is contained in a type list
template <typename tType, typename...>
struct Contains : std::false_type { };

template <typename tType, typename tHead, typename... tRest>
struct Contains<tType, tHead, tRest...> : std::conditional_t<std::is_same_v<tType, tHead>, std::true_type, Contains<tType, tRest...>> { };

// Check if all types in the list are unique
template <typename...>
struct IsUnique : std::true_type { };

template <typename tType, typename... tRest>
struct IsUnique<tType, tRest...> : std::conditional_t<Contains<tType, tRest...>::value, std::false_type, IsUnique<tRest...>> { };

// Get the index of a type tType in the parameter pack
template <typename tType, typename...>
struct IndexOf { static constexpr int cValue = -1; };

template <typename tType, typename tHead, typename... tRest>
struct IndexOf<tType, tHead, tRest...>
{
	static constexpr size_t cValue = std::is_same_v<tType, tHead> ? 0 : 1 + IndexOf<tType, tRest...>::cValue;
};

// ==== BitFlags Class ====

template <typename... tType>
class BitFlags {
	static_assert(IsUnique<tType...>::value, "BitFlags requires all flag types to be unique.");

public:
	BitFlags() = default;
	BitFlags(std::initializer_list<bool> aList)
	{
		for (int i = 0; i < gStaticCast<int>(aList.size()); i++)
			SetFlag(i, *(aList.begin() + i));
	}

	static constexpr size_t cCount = sizeof...(tType);
	static constexpr size_t cStorageSize = (cCount + 7) / 8;

	template <typename T>
	bool GetFlag() const
	{
		static_assert(Contains<T, tType...>::value, "tType must be one of the BitFlags types.");
		constexpr size_t index = IndexOf<T, tType...>::cValue;
		return (mFlags[index / 8] >> (index % 8)) & 0x1;
	}

	template <typename T>
	void SetFlag(bool aValue)
	{
		static_assert(Contains<T, tType...>::value, "tType must be one of the BitFlags types.");
		constexpr size_t index = IndexOf<T, tType...>::cValue; // <-- Full template parameter list!
		SetFlag((int)index, aValue);
	}

	void SetFlag(int aIndex, bool aValue)
	{
		if (aValue)
			mFlags[aIndex / 8] |= (1 << (aIndex % 8));
		else
			mFlags[aIndex / 8] &= ~(1 << (aIndex % 8));
	}

	template <typename T>
	void ToggleFlag()
	{
		static_assert(Contains<T, tType...>::value, "tType must be one of the BitFlags types.");
		constexpr size_t index = IndexOf<T, tType...>::cValue;
		mFlags[index / 8] ^= (1 << (index % 8));
	}

private:
	StaticArray<uint8, cStorageSize> mFlags { 0 };
};

}