#pragma once
// External includes
#include <External/nlohmann/json.hpp>

// Std includes
#include <type_traits>

namespace DC
{

using Json = nlohmann::ordered_json;

template <typename, typename T>
struct HasToJson {
	static_assert(
		std::integral_constant<T, false>::value,
		"Second template parameter needs to be of function type.");
};

template <typename C, typename Ret, typename... Args>
struct HasToJson<C, Ret(Args...)> {
private:
	template <typename T>
	static constexpr auto check(T*) ->
		typename std::is_same<decltype(std::declval<T>().ToJson()), Ret>::type;

	template <typename>
	static constexpr std::false_type check(...);

	typedef decltype(check<C>(0)) type;

public:
	static constexpr bool value = type::value;
};

template <typename, typename T>
struct HasFromJson {
	static_assert(
		std::integral_constant<T, false>::value,
		"Second template parameter needs to be of function type.");
};

template <typename C, typename Ret, typename... Args>
struct HasFromJson<C, Ret(Args...)> {
private:
	template <typename T>
	static constexpr auto check(T*) ->
		typename std::is_same<decltype(std::declval<T>().FromJson(std::declval<Args>()...)), Ret>::type;

	template <typename>
	static constexpr std::false_type check(...);

	typedef decltype(check<C>(0)) type;

public:
	static constexpr bool value = type::value;
};

// Template function for to_json
template<typename T>
typename std::enable_if<HasToJson<T, Json()>::value>::type
to_json(Json& j, const T* obj) 
{
	j = obj->ToJson();
}

template<typename T>
typename std::enable_if<HasFromJson<T, void(const Json&)>::value>::type
from_json(const Json& j, T* obj) 
{
	obj->FromJson(j);
}

template<typename T>
typename std::enable_if<HasToJson<T, Json()>::value>::type
to_json(Json& j, const T& obj) 
{
	j = obj.ToJson();
}

template<typename T>
typename std::enable_if<HasFromJson<T, void(const Json&)>::value>::type
from_json(const Json& j, T& obj) 
{
	obj.FromJson(j);
}

}

#define JSON_SAVE(ioJson, inValue) (ioJson)[#inValue] = inValue
#define JSON_LOAD(inJson, outValue) if (inJson.contains(#outValue)) outValue = (inJson)[#outValue]