#pragma once
// DuckCore includes
#include <DuckCore/Config.h>

// Std includes
#include <DuckCore/Threads/Atomic.h>

#include <mutex>
#include <shared_mutex>

#define THREADLOCAL thread_local 

namespace DC
{
class MutexBase
{
public:
	IF_ASSERTS(virtual bool IsLockedByCurrentThread() const;) 
};

class Mutex : public MutexBase
{
public:
	void Lock();
	bool TryLock(); // Returns true if locked successfully.
	void Unlock();

private:
	std::mutex mMutex;
};

class ReadWriteMutex : public MutexBase
{
public:
	void WriteLock();
	bool TryWriteLock(); // Tries to write lock the mutex. Returns true if successful.
	void WriteUnlock();

	void ReadLock();
	bool TryReadLock(); // Tries to read lock the mutex. Returns true if successful.
	void ReadUnlock();

private:
	std::shared_mutex mMutex;
};

class RecursiveMutex : public MutexBase
{
public:
	void Lock();
	bool TryLock(); // Returns true if locked successfully.
	void Unlock();

	IF_ASSERTS(virtual bool IsLockedByCurrentThread() const override;) 

private:
	std::recursive_mutex mMutex;
};
}
