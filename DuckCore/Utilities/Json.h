#pragma once
// External includes
#include <External/nlohmann/json.hpp>

// Std includes
#include <type_traits>

namespace DC
{

using Json = nlohmann::ordered_json;

template <typename, typename taType>
struct HasToJson {
	static_assert(
		std::integral_constant<taType, false>::value,
		"Second template parameter needs to be of function type.");
};

template <typename taC, typename taRet, typename... taArgs>
struct HasToJson<taC, taRet(taArgs...)> {
private:
	template <typename taType>
	static constexpr auto check(taType*) ->
		typename std::is_same<decltype(std::declval<taType>().ToJson()), taRet>::type;

	template <typename>
	static constexpr std::false_type check(...);

	typedef decltype(check<taC>(0)) type;

public:
	static constexpr bool value = type::value;
};

template <typename, typename T>
struct HasFromJson {
	static_assert(
		std::integral_constant<T, false>::value,
		"Second template parameter needs to be of function type.");
};

template <typename taC, typename taRet, typename... taArgs>
struct HasFromJson<taC, taRet(taArgs...)> {
private:
	template <typename taType>
	static constexpr auto check(taType*) ->
		typename std::is_same<decltype(std::declval<taType>().FromJson(std::declval<taArgs>()...)), taRet>::type;

	template <typename>
	static constexpr std::false_type check(...);

	typedef decltype(check<taC>(0)) type;

public:
	static constexpr bool value = type::value;
};

// Template function for to_json
template<typename T>
std::enable_if_t<HasToJson<T, Json()>::value>
ToJson(Json& outJson, const T* aObject) 
{
	if (aObject != nullptr)
		outJson = aObject->ToJson();
}

template<typename T>
std::enable_if_t<HasToJson<T, Json()>::value>
ToJson(Json& outJson, const T& aObject) 
{
	outJson = aObject.ToJson();
}

template<typename T>
std::enable_if_t<HasFromJson<T, void(const Json&)>::value>
FromJson(const Json& aJson, T& outObject) 
{
	outObject.FromJson(aJson);
}

template<typename taType>
void to_json(Json& outJson, const taType& aObject)
{
	ToJson(outJson, aObject);
}

template<typename taType>
void from_json(const Json& aJson, taType& outObject)
{
	FromJson(aJson, outObject);
}

}

#define JSON_SAVE(ioJson, inValue) (ioJson)[#inValue] = inValue
#define JSON_LOAD(inJson, outValue) if (auto it = inJson.find(#outValue); it != inJson.end()) outValue = it.value();