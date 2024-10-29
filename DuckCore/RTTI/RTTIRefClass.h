#pragma once
#include <DuckCore/RTTI/RTTIClass.h>
#include <DuckCore/Threads/Atomic.h>

namespace DC
{

class RTTIRefClass : public RTTIClass
{
	RTTI_CLASS(RTTIRefClass, RTTIClass)

public:
	RTTIRefClass()
	{
		mWeakRefCounter = new WeakRefCounter();
	}

	virtual ~RTTIRefClass() override
	{
		mWeakRefCounter->mIsAlive = false;
		if (mWeakRefCounter->mRefCount <= 0)
			delete mWeakRefCounter;
	}

	int32 GetRefCount() const { return mRefCount; }
	int32 GetWeakRefCount() const { return mWeakRefCounter != nullptr ? static_cast<int32>(mWeakRefCounter->mRefCount) : 0; }

private:
	struct WeakRefCounter
	{
		bool mIsAlive = true;
		Atomic<int32> mRefCount = 0;
	};
	Atomic<int32> mRefCount = 0;

	WeakRefCounter* mWeakRefCounter = nullptr;

	// This is an invalid weak ref counter to be used when nullptr is passed. It always keeps 1 reference to itself to prevent it's destruction
	inline static WeakRefCounter sInvalidWeakRefCounter = { false, 1 };

	template<typename taRefClassType>
	friend class Ref;

	template<typename taRefClassType>
	friend class WeakRef;
};

}
