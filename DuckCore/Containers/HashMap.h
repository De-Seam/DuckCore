#pragma once
#include <DuckCore/Config.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Utilities/Json.h>

#pragma warning( push )
#pragma warning( disable : 4702 )
#include <External/phmap/phmap.h>
#pragma warning( pop )


namespace DC
{
template<typename taKey, typename taValue>
class HashMap
{
public:
	HashMap() = default;

	taValue& operator[](const taKey& inKey) { return mMap[inKey]; }
	const taValue& At(const taKey& inKey) const { return mMap.at(inKey); }
	taValue& At(const taKey& inKey) { return mMap.at(inKey); }

	void Add(const taKey& inKey, const taValue& inValue);
	bool Remove(const taKey& inKey) { return mMap.erase(inKey); }

	void Clear() { mMap.clear(); }

	bool IsEmpty() const { return mMap.empty(); }
	int Length() const { return static_cast<int>(mMap.size()); }
	bool Contains(const taKey& inKey) const { return mMap.contains(inKey); }

	taValue* Find(const taKey& inKey);
	const taValue* Find(const taKey& inKey) const;

	template<typename taLambda>
	void ForEach(taLambda&& inLambda);
	template<typename taLambda>
	void ForEach(taLambda&& inLambda) const;

	template<typename taPredicate>
	int RemoveIf(taPredicate&& inPredicate); // Returns amount removed

	Json ToJson() const;
	void FromJson(const Json& inJson);

private:
	phmap::flat_hash_map<taKey, taValue> mMap;
};

template<typename taKey, typename taValue>
inline void ToJson(Json& outJson, const HashMap<taKey, taValue>& inHashMap)
{
	gAssert(outJson.empty());
	inHashMap.ForEach([&outJson](const taKey& inKey, const taValue& inValue)
	{
		outJson.push_back(Json::array( {inKey, inValue} ));
	});
}

template<typename taKey, typename taValue>
inline void FromJson(const Json& inJson, HashMap<taKey, taValue>& outHashMap)
{
	gAssert(inJson.is_array());

	for (const auto& element : inJson)
		outHashMap.Add(element.at(0).template get<taKey>(), element.at(1).template get<taValue>());
}

template <typename taKey, typename taValue>
void HashMap<taKey, taValue>::Add(const taKey& inKey, const taValue& inValue)
{
	mMap.emplace(inKey, inValue);
}

template <typename taKey, typename taValue>
taValue* HashMap<taKey, taValue>::Find(const taKey& inKey)
{
	auto it = mMap.find(inKey);
	if (it != mMap.end())
		return &it->second;
	return nullptr;
}

template <typename taKey, typename taValue>
const taValue* HashMap<taKey, taValue>::Find(const taKey& inKey) const
{
	auto it = mMap.find(inKey);
	if (it != mMap.end())
		return &it->second;
	return nullptr;
}

template<typename taKey, typename taValue>
template<typename taLambda>
void HashMap<taKey, taValue>::ForEach(taLambda&& inLambda)
{
	for (auto& [key, value] : mMap)
		inLambda(key, value);
}

template<typename taKey, typename taValue>
template<typename taLambda>
void HashMap<taKey, taValue>::ForEach(taLambda&& inLambda) const
{
	for (const auto& [key, value] : mMap)
		inLambda(key, value);
}

template<typename taKey, typename taValue>
template<typename taPredicate>
int HashMap<taKey, taValue>::RemoveIf(taPredicate&& inPredicate)
{
	int removed_count = 0;
	for (auto it = mMap.begin(); it != mMap.end();) 
	{
		if (inPredicate(it->first, it->second))
		{
			removed_count++;
			mMap.erase(it->first);
		}
		else
		{
			it++;
		}
	}
	return removed_count;
}

template <typename taKey, typename taValue>
Json HashMap<taKey, taValue>::ToJson() const
{
	Json json;
	ForEach([&json](const taKey& inKey, const taValue& inValue)
	{
		json.push_back(Json::array( {inKey, inValue} ));
	});
	return json;
}

template <typename taKey, typename taValue>
void HashMap<taKey, taValue>::FromJson(const Json& inJson)
{
	gAssert(inJson.is_array());

	for (const auto& element : inJson)
		Add(element.at(0).template get<taKey>(), element.at(1).template get<taValue>());
}
}
