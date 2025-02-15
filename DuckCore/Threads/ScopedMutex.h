#pragma once
#include <DuckCore/Threads/Mutex.h>

namespace DC
{
class ScopedMutexLock
{
public:
	ScopedMutexLock() = default;
	ScopedMutexLock(Mutex& inMutex);
	~ScopedMutexLock();

	void SetLockedMutex(Mutex& inMutex); // Set the mutex that should already be locked, because we will unlock it in our destructor.
	void Lock(Mutex& inMutex); // Lock the mutex. This is useful if you want to lock the mutex after construction.

private:
	Mutex* mMutex = nullptr;
};

class ScopedMutexWriteLock
{
public:
	ScopedMutexWriteLock(ReadWriteMutex& inMutex);
	~ScopedMutexWriteLock();

private:
	ReadWriteMutex* mMutex = nullptr;
};

class ScopedMutexReadLock
{
public:
	ScopedMutexReadLock(ReadWriteMutex& inMutex);
	~ScopedMutexReadLock();

private:
	ReadWriteMutex* mMutex = nullptr;
};

class ScopedMutexRecursiveLock
{
public:
	ScopedMutexRecursiveLock(RecursiveMutex& inMutex);
	~ScopedMutexRecursiveLock();

private:
	RecursiveMutex* mMutex = nullptr;
};
}
