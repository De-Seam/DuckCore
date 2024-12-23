#pragma once
// Core includes
#include <DuckCore/Config.h>

// External includes
#include <External/phmap/phmap.h>

namespace DC
{
template<typename taKey>
class HashSet
{
public:
	HashSet() = default;

	void Add(const taKey& inKey) { mSet.insert(inKey); }
	bool Remove(const taKey& inKey) { return mSet.erase(inKey); }

	void Clear() { mSet.clear(); }

	bool IsEmpty() const { return mSet.empty(); }
	int Length() const { return static_cast<int>(mSet.size()); }
	bool Contains(const taKey& inKey) const { return mSet.contains(inKey); }

	taKey* Find(const taKey& inKey);
	const taKey* Find(const taKey& inKey) const;

private:
	phmap::flat_hash_set<taKey> mSet;
};

template <typename taKey>
taKey* HashSet<taKey>::Find(const taKey& inKey)
{
	auto it = mSet.find(inKey);
	if (it != mSet.end())
		return &*it;
	return nullptr;
}

template <typename taKey>
const taKey* HashSet<taKey>::Find(const taKey& inKey) const
{
	auto it = mSet.find(inKey);
	if (it != mSet.end())
		return &*it;
	return nullptr;
}
}
