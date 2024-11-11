#pragma once
// Core includes
#include <DuckCore/Config.h>

// External includes
#include <External/phmap/phmap.h>

namespace DC
{
template<typename taKey, typename taValue>
class HashMap
{
public:
	HashMap() = default;

	taValue& operator[](const taKey& inKey) { return mMap[inKey]; }
	const taValue& operator[](const taKey& inKey) const { return mMap.at(inKey); }

	bool Remove(const taKey& inKey) { return mMap.erase(inKey); }

	void Clear() { mMap.clear(); }

	bool IsEmpty() const { return mMap.empty(); }
	bool Contains(const taKey& inKey) const { return mMap.contains(inKey); }

	taValue* Find(const taKey& inKey);
	const taValue* Find(const taKey& inKey) const;

	template<typename taLambda>
	void ForEach(taLambda&& inLambda);

private:
	phmap::flat_hash_map<taKey, taValue> mMap;
};

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

}
