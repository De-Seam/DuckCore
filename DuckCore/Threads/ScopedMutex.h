#pragma once
#include <DuckCore/Threads/Mutex.h>

namespace DC
{
class ScopedMutexLock
{
public:
	ScopedMutexLock(Mutex& inMutex);
	~ScopedMutexLock();

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
