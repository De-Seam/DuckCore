#pragma once
// Core includes
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Threads/Atomic.h>
#include <DuckCore/Utilities/Json.h>
#include <DuckCore/Utilities/NoCopy.h>

namespace DC
{

class RTTIClass;

class RefClass : public NoCopy, public NoMove
{
public:
	virtual ~RefClass()
	{
		if (mWeakRefCounter != nullptr)
			mWeakRefCounter->mIsAlive = false;
	}

	int32 GetRefCount() const { return mRefCount; }
	int32 GetWeakRefCount() const { return mWeakRefCounter != nullptr ? static_cast<int32>(mWeakRefCounter->mRefCount) : 0; }

private:
	Atomic<int32> mRefCount = 0;

	struct WeakRefCounter
	{
		bool mIsAlive = true;
		Atomic<int32> mRefCount = 0;
	};
	WeakRefCounter* mWeakRefCounter = nullptr;

	// This is an invalid weak ref counter to be used when nullptr is passed. It always keeps 1 reference to itself to prevent its destruction
	inline static WeakRefCounter sInvalidWeakRefCounter = { false, 1 };

	template<typename taRefClassType>
	friend class Ref;

	template<typename taRefClassType>
	friend class WeakRef;
};

template<typename taType>
class WeakRef;

template<typename taType>
class Ref
{
	using NonConstType = std::remove_const_t<taType>;
public:
	Ref() = default;

	Ref(const Ref<taType>& inOther)
	{
		if (inOther.mPtr != nullptr)
		{
			gAssert(inOther.mPtr->mRefCount > 0 && "Ref object is already destroyed!");
			mPtr = inOther.mPtr;
			const_cast<NonConstType*>(mPtr)->mRefCount++;
		}
	}

	Ref(Ref<taType>&& inOther)
	{
		mPtr = inOther.mPtr;
		if (mPtr != nullptr)
			const_cast<NonConstType*>(mPtr)->mRefCount++; ///< Increment ref count because it will be decremented later.
	}

	Ref<taType>& operator=(const Ref<taType>& inOther)
	{
		if (mPtr != nullptr)
		{
			const_cast<NonConstType*>(mPtr)->mRefCount--;
			if (mPtr->mRefCount <= 0)
				delete mPtr;
		}

		mPtr = inOther.mPtr;
		if (mPtr != nullptr)
		{
			gAssert(mPtr->mRefCount > 0 && "Ref object is already destroyed!");
			const_cast<NonConstType*>(mPtr)->mRefCount++;
		}
		return *this;
	}

	//TODO: Move operator

	// Construct a ref from self
	Ref(taType* inSelf)
	{
		static_assert(std::is_base_of_v<RefClass, taType>);
		mPtr = inSelf;
		if (mPtr != nullptr)
			const_cast<NonConstType*>(mPtr)->mRefCount++;
	}

	template<typename taParentClass>
	Ref(const Ref<taParentClass>& inOther)
	{
		static_assert(std::is_base_of_v<taParentClass, taType> || std::is_base_of_v<taType, taParentClass>);
		if (inOther.mPtr != nullptr)
		{
			gAssert(inOther.mPtr->mRefCount > 0 && "Ref object is already destroyed!");
			mPtr = static_cast<taType*>(inOther.mPtr);
			const_cast<NonConstType*>(mPtr)->mRefCount++;
		}
	}

	~Ref()
	{
		if (mPtr != nullptr)
		{
			const_cast<NonConstType*>(mPtr)->mRefCount--;

			if (mPtr->mRefCount <= 0)
				delete mPtr;
		}
	}

	taType* Get() const { return mPtr; }
	taType* operator->() const { return mPtr; }
	operator taType*() const { return mPtr; }

	bool operator==(const Ref<taType>& inOther) const { return mPtr == inOther.mPtr; }
	bool operator==(const taType* inOther) const { return mPtr == inOther; }
	bool operator!=(const Ref<taType>& inOther) const { return mPtr != inOther.mPtr; }
	bool operator!=(const taType* inOther) const { return mPtr != inOther; }

	bool IsValid() const { return mPtr != nullptr; }

private:
	taType* mPtr = nullptr;

private:
	// Private so only WeakRef can use it
	Ref(const WeakRef<taType>& inOther)
	{
		gAssert(inOther.IsAlive() && "Invalid Weak Ref passed!");
		gAssert(inOther.mPtr->mRefCount > 0 && "Ref object is already destroyed!");
		mPtr = inOther.mPtr;
		mPtr->mRefCount++;
	}

	template<typename taRefClassType>
	friend class Ref;

	template<typename taRefClassType>
	friend class WeakRef;
};

template<typename taType>
class WeakRef
{
public:
	WeakRef(taType* inPtr = nullptr)
	{
		mPtr = inPtr;
		mWeakRefCounter = mPtr != nullptr ? mPtr->mWeakRefCounter : &RefClass::sInvalidWeakRefCounter;

		if (mWeakRefCounter == nullptr)
		{
			mPtr->mWeakRefCounter = mWeakRefCounter;
			mWeakRefCounter = new RefClass::WeakRefCounter();
		}

		mWeakRefCounter->mRefCount++;
	}

	WeakRef(const Ref<taType>& inRef)
	{
		mPtr = inRef.mPtr;
		mWeakRefCounter = mPtr != nullptr ? mPtr->mWeakRefCounter : &RefClass::sInvalidWeakRefCounter;

		if (mWeakRefCounter == nullptr)
		{
			mPtr->mWeakRefCounter = mWeakRefCounter;
			mWeakRefCounter = new RefClass::WeakRefCounter();
		}

		mWeakRefCounter->mRefCount++;
	}

	WeakRef(const WeakRef<taType>& inWeakRef)
	{
		mPtr = inWeakRef.mPtr;
		mWeakRefCounter = inWeakRef.mWeakRefCounter;

		mWeakRefCounter->mRefCount++;
	}

	WeakRef<taType>& operator=(const WeakRef<taType>& inOther)
	{
		if (mWeakRefCounter != inOther.mWeakRefCounter)
		{
			if (--mWeakRefCounter->mRefCount <= 0 && !mWeakRefCounter->mIsAlive)
			{
				delete mWeakRefCounter;
			}
			mPtr = inOther.mPtr;
			mWeakRefCounter = inOther.mWeakRefCounter;
			if (mWeakRefCounter != nullptr)
			{
				mWeakRefCounter->mRefCount++;
			}
		}
		return *this;
	}

	~WeakRef()
	{
		mWeakRefCounter->mRefCount--;
		// If this was the last Ref and WeakRef referencing the ptr then we can destroy the all ref count
		if (mWeakRefCounter->mRefCount <= 0)
		{
			// Only destroy it if the object is already destroyed
			if (!mWeakRefCounter->mIsAlive)
				delete mWeakRefCounter;
		}
	}

	[[deprecated]] // use Ref() instead.
	Ref<taType> Get()
	{
		return Ref();
	}

	Ref<taType> Ref()
	{
	    gAssert(IsAlive() && "Can't make a reference if it isn't alive anymore. Check IsAlive() first");
		return mPtr;
	}

	bool IsAlive() const { return mWeakRefCounter->mIsAlive; }

	bool operator==(const WeakRef<taType>& inOther) const { return mPtr == inOther.mPtr; }

private:
	taType* mPtr = nullptr;
	RefClass::WeakRefCounter* mWeakRefCounter = nullptr;

	template<typename taRefClassType>
	friend class Ref;
};
}
