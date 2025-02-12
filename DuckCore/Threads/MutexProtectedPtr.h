#pragma once
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Threads/Mutex.h>

namespace DC
{
template<typename taType>
class MutexReadProtectedPtr
{
public:
	MutexReadProtectedPtr(ReadWriteMutex& inMutex, taType* inPtr, bool inAlreadyLocked = false) :
		mPtr(inPtr), mMutex(&inMutex)
	{
		if (!inAlreadyLocked)
			mMutex->ReadLock();
	}

	~MutexReadProtectedPtr()
	{
		if (mMutex)
			mMutex->ReadUnlock();
	}

	MutexReadProtectedPtr(const MutexReadProtectedPtr&) = delete;
	MutexReadProtectedPtr& operator=(const MutexReadProtectedPtr&) = delete;

	// Move constructor
	MutexReadProtectedPtr(MutexReadProtectedPtr&& inOther) noexcept :
		mPtr(inOther.mPtr), mMutex(inOther.mMutex)
	{
		inOther.mMutex = nullptr; // Prevent the destructor of 'other' from unlocking the mutex
	}

	// Move assignment operator
	MutexReadProtectedPtr& operator=(MutexReadProtectedPtr&& inOther) noexcept
	{
		if (this != &inOther)
		{
			// Safely unlock the current mutex if it exists
			if (mMutex)
			{
				mMutex->ReadUnlock();
			}

			// Transfer ownership
			mPtr = inOther.mPtr;
			mMutex = inOther.mMutex;
			inOther.mMutex = nullptr; // Prevent the destructor of 'other' from unlocking the mutex
		}
		return *this;
	}

	taType* operator->()
	{
		return Get();
	}

	const taType* operator->() const
	{
		return Get();
	}

	taType* Get()
	{
		gAssert(mMutex != nullptr, "The mutex was unlocked, access to the object denied!");
		return mPtr;
	}

	const taType* Get() const
	{
		gAssert(mMutex != nullptr, "The mutex was unlocked, access to the object denied!");
		return mPtr;
	}

	void Unlock()
	{
		gAssert(mMutex != nullptr, "The mutex was already unlocked!");
		mMutex->ReadUnlock();
		mMutex = nullptr;
	}

private:
	taType* mPtr = nullptr;
	ReadWriteMutex* mMutex = nullptr;
};

template<typename taType>
class MutexWriteProtectedPtr
{
public:
	MutexWriteProtectedPtr(ReadWriteMutex& inMutex, taType* inPtr, bool inAlreadyLocked = false) : mPtr(inPtr), mMutex(&inMutex)
	{
		if (!inAlreadyLocked)
			mMutex->WriteLock();
	}

	~MutexWriteProtectedPtr()
	{
		if (mMutex)
			mMutex->WriteUnlock();
	}

	MutexWriteProtectedPtr(const MutexWriteProtectedPtr&) = delete;
	MutexWriteProtectedPtr& operator=(const MutexWriteProtectedPtr&) = delete;

	// Move constructor
	MutexWriteProtectedPtr(MutexWriteProtectedPtr&& inOther) noexcept : mPtr(inOther.mPtr), mMutex(inOther.mMutex)
	{
		inOther.mMutex = nullptr; // Prevent the destructor of 'other' from unlocking the mutex
	}

	// Move assignment operator
	MutexWriteProtectedPtr& operator=(MutexWriteProtectedPtr&& inOther) noexcept
	{
		if (this != &inOther)
		{
			// Safely unlock the current mutex if it exists
			if (mMutex)
			{
				mMutex->WriteUnlock();
			}

			// Transfer ownership
			mPtr = inOther.mPtr;
			mMutex = inOther.mMutex;
			inOther.mMutex = nullptr; // Prevent the destructor of 'other' from unlocking the mutex
		}
		return *this;
	}

	taType* operator->() { return mPtr; }

	const taType* operator->() const { return mPtr; }

	taType* Get()
	{
		gAssert(mMutex != nullptr, "The mutex was unlocked, access to the object denied!");
		return mPtr;
	}

	const taType* Get() const
	{
		gAssert(mMutex != nullptr, "The mutex was unlocked, access to the object denied!");
		return mPtr;
	}

	void Unlock()
	{
		gAssert(mMutex != nullptr, "The mutex was already unlocked!");
		mMutex->WriteUnlock();
		mMutex = nullptr;
	}

private:
	taType* mPtr = nullptr;
	ReadWriteMutex* mMutex = nullptr;
};
}
