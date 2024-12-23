#pragma once
// External includes
#include <External/nlohmann/json.hpp>

// Std includes
#include <type_traits>

namespace DC
{

using Json = nlohmann::ordered_json;

template <typename, typename T>
struct has_serialize {
	static_assert(
		std::integral_constant<T, false>::value,
		"Second template parameter needs to be of function type.");
};

template <typename C, typename Ret, typename... Args>
struct has_serialize<C, Ret(Args...)> {
private:
	template <typename T>
	static constexpr auto check(T*) ->
		typename std::is_same<decltype(std::declval<T>().Serialize()), Ret>::type;

	template <typename>
	static constexpr std::false_type check(...);

	typedef decltype(check<C>(0)) type;

public:
	static constexpr bool value = type::value;
};

template <typename, typename T>
struct has_deserialize {
	static_assert(
		std::integral_constant<T, false>::value,
		"Second template parameter needs to be of function type.");
};

template <typename C, typename Ret, typename... Args>
struct has_deserialize<C, Ret(Args...)> {
private:
	template <typename T>
	static constexpr auto check(T*) ->
		typename std::is_same<decltype(std::declval<T>().Deserialize(std::declval<Args>()...)), Ret>::type;

	template <typename>
	static constexpr std::false_type check(...);

	typedef decltype(check<C>(0)) type;

public:
	static constexpr bool value = type::value;
};

// Template function for to_json
template<typename T>
typename std::enable_if<has_serialize<T, Json()>::value>::type
to_json(Json& j, const T* obj) 
{
	j = obj->Serialize();
}

template<typename T>
typename std::enable_if<has_deserialize<T, void(const Json&)>::value>::type
from_json(const Json& j, T* obj) 
{
	obj->Deserialize(j);
}

template<typename T>
typename std::enable_if<has_serialize<T, Json()>::value>::type
to_json(Json& j, const T& obj) 
{
	j = obj.Serialize();
}

template<typename T>
typename std::enable_if<has_deserialize<T, void(const Json&)>::value>::type
from_json(const Json& j, T& obj) 
{
	obj.Deserialize(j);
}

}

#define JSON_SAVE(ioJson, inValue) (ioJson)[#inValue] = inValue
#define JSON_LOAD(inJson, outValue) if (inJson.contains(#outValue)) outValue = (inJson)[#outValue]