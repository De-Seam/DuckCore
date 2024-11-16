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
	int Length() const { return static_cast<int>(mMap.size()); }
	bool Contains(const taKey& inKey) const { return mMap.contains(inKey); }

	std::optional<taValue> Find(const taKey& inKey);
	std::optional<const taValue> Find(const taKey& inKey) const;

	template<typename taLambda>
	void ForEach(taLambda&& inLambda);

	template<typename taPredicate>
	int RemoveIf(taPredicate&& inPredicate); // Returns amount removed

private:
	phmap::flat_hash_map<taKey, taValue> mMap;
};

template <typename taKey, typename taValue>
std::optional<taValue> HashMap<taKey, taValue>::Find(const taKey& inKey)
{
	auto it = mMap.find(inKey);
	if (it != mMap.end())
		return it->second;
	return std::nullopt;
}

template <typename taKey, typename taValue>
std::optional<const taValue> HashMap<taKey, taValue>::Find(const taKey& inKey) const
{
	auto it = mMap.find(inKey);
	if (it != mMap.end())
		return it->second;
	return std::nullopt;
}

template<typename taKey, typename taValue>
template<typename taLambda>
void HashMap<taKey, taValue>::ForEach(taLambda&& inLambda)
{
	for (auto& [key, value] : mMap)
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
}
