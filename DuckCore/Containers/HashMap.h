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
	class Iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = std::pair<const taKey, taValue>;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;
	
		explicit Iterator(typename phmap::flat_hash_map<taKey, taValue>::iterator aIterator, bool aIsValid) : mIterator(aIterator), mIsValid(aIsValid) {}
	
		reference operator*() const { gAssert(IsValid()); return *mIterator; }
		pointer operator->() const { gAssert(IsValid()); return &(*mIterator); }
	
		Iterator& operator++()
		{
			gAssert(IsValid());
			++mIterator;
			return *this;
		}
	
		Iterator operator++(int)
		{
			gAssert(IsValid());
			Iterator temp = *this;
			 ++mIterator;
	        return temp;
		}
	
		bool operator==(const Iterator& other) const { return mIterator == other.mIterator; }
		bool operator!=(const Iterator& other) const { return mIterator != other.mIterator; }
		operator bool() const { return IsValid(); }

		bool IsValid() const { return mIsValid; }
		const taKey& GetKey() const { gAssert(IsValid()); return mIterator->first; }
		taValue& GetValue() { gAssert(IsValid()); return mIterator->second; }
		const taValue& GetValue() const { gAssert(IsValid()); return mIterator->second; }

	private:
		typename phmap::flat_hash_map<taKey, taValue>::iterator mIterator;
		bool mIsValid = false;
	};

	class IteratorC
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = std::pair<const taKey, const taValue>;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;

		IteratorC(typename HashMap<taKey, taValue>::Iterator aIterator) : mIterator(aIterator), mIsValid(aIterator.IsValid()) {}
		explicit IteratorC(typename phmap::flat_hash_map<taKey, taValue>::iterator aIterator, bool aIsValid) : mIterator(aIterator), mIsValid(aIsValid) {}
		explicit IteratorC(typename phmap::flat_hash_map<taKey, taValue>::const_iterator aIterator, bool aIsValid) : mIterator(aIterator), mIsValid(aIsValid) {}

		reference operator*() const { gAssert(IsValid()); return *mIterator; }
		pointer operator->() const { gAssert(IsValid()); return &(*mIterator); }

		IteratorC& operator++()
		{
			++mIterator;
			return *this;
		}

		IteratorC operator++(int)
		{
			IteratorC temp = *this;
			++mIterator;
			return temp;
		}

		bool operator==(const IteratorC& aOther) const { return mIterator == aOther.mIterator; }
		bool operator!=(const IteratorC& aOther) const { return mIterator != aOther.mIterator; }
		operator bool() const { return IsValid(); }

		bool IsValid() const { return mIsValid; }
		const taKey& GetKey() const { gAssert(IsValid()); return mIterator->first; }
		const taValue& GetValue() const { gAssert(IsValid()); return mIterator->second; }

	private:
		typename phmap::flat_hash_map<taKey, taValue>::const_iterator mIterator;
		bool mIsValid = false;
	};
		
	Iterator begin() { return Iterator(mMap.begin(), !mMap.empty()); }
	Iterator end() { return Iterator(mMap.end(), false); }

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

	Iterator Find(const taKey& inKey);
	IteratorC Find(const taKey& inKey) const;

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
typename HashMap<taKey, taValue>::Iterator HashMap<taKey, taValue>::Find(const taKey& inKey)
{
	typename phmap::flat_hash_map<taKey, taValue>::iterator iter = mMap.find(inKey);
	return typename HashMap<taKey, taValue>::Iterator(iter, iter != mMap.end());
}

template <typename taKey, typename taValue>
typename HashMap<taKey, taValue>::IteratorC HashMap<taKey, taValue>::Find(const taKey& inKey) const
{
	typename phmap::flat_hash_map<taKey, taValue>::const_iterator iter = mMap.find(inKey);
	return typename HashMap<taKey, taValue>::IteratorC(iter, iter != mMap.end());
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
