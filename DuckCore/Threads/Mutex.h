#pragma once
// Std includes
#include <mutex>
#include <shared_mutex>

#define THREADLOCAL thread_local 

namespace DC
{
class Mutex
{
public:
	void Lock();
	void Unlock();

private:
	std::mutex mMutex;
};

class ReadWriteMutex
{
public:
	void WriteLock();
	void WriteUnlock();

	void ReadLock();
	void ReadUnlock();

private:
	std::shared_mutex mMutex;
};
}
