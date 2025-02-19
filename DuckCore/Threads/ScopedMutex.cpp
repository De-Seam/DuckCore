#include <DuckCore/Threads/ScopedMutex.h>

#include <DuckCore/Core/Assert.h>

namespace DC
{
ScopedMutexLock::ScopedMutexLock(Mutex &inMutex) : 
	mMutex(&inMutex) 
{ 
	mMutex->Lock(); 
}

ScopedMutexLock::~ScopedMutexLock() 
{
	if (mMutex != nullptr)
		mMutex->Unlock();
}

void ScopedMutexLock::SetLockedMutex(Mutex& inMutex)
{
	gAssert(inMutex.IsLockedByCurrentThread());
	mMutex = &inMutex;
}

void ScopedMutexLock::Lock(Mutex& inMutex)
{
	mMutex = &inMutex;
	mMutex->Lock();
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

ScopedMutexRecursiveLock::ScopedMutexRecursiveLock(RecursiveMutex& inMutex) :
	mMutex(&inMutex)
{
	mMutex->Lock();	
}

ScopedMutexRecursiveLock::~ScopedMutexRecursiveLock()
{
	mMutex->Unlock();
}
}
