#include <DuckCore/Threads/ScopedMutex.h>

namespace DC
{
ScopedMutexLock::ScopedMutexLock(Mutex &inMutex) : 
	mMutex(&inMutex) 
{ 
	mMutex->Lock(); 
}

ScopedMutexLock::~ScopedMutexLock() 
{
	mMutex->Unlock();
}

ScopedMutexWriteLock::ScopedMutexWriteLock(ReadWriteMutex& inMutex) : 
	mMutex(&inMutex)
{
	mMutex->WriteLock();
}

ScopedMutexWriteLock::~ScopedMutexWriteLock() 
{
	mMutex->WriteUnlock();
}

ScopedMutexReadLock::ScopedMutexReadLock(ReadWriteMutex& inMutex) :
	mMutex(&inMutex)
{
	mMutex->ReadLock();
}

ScopedMutexReadLock::~ScopedMutexReadLock() 
{
	mMutex->ReadUnlock();
}
}