#include "Mutex.h"

// Core includes
#include <DuckCore/Containers/Array.h>

#include "DuckCore/Core/Assert.h"

using namespace DC;

#ifdef _ASSERTS
THREADLOCAL Array<const Mutex*> gLockedMutexes;
THREADLOCAL Array<const ReadWriteMutex*> gLockedReadWriteMutexes;

void gRegisterLockMutex(const Mutex* inMutex)
{
	gAssert(!gLockedMutexes.Contains(inMutex), "Mutex is already locked by same thread");
	gLockedMutexes.Add(inMutex);
}

void gRegisterUnlockMutex(const Mutex* inMutex)
{
	gAssert(gLockedMutexes.Contains(inMutex), "Mutex is not locked by this thread");
	gLockedMutexes.SwapRemove(gLockedMutexes.Find(inMutex));
}

void gRegisterLockMutex(const ReadWriteMutex* inMutex)
{
    gAssert(!gLockedReadWriteMutexes.Contains(inMutex), "Mutex is already locked by same thread");
	gLockedReadWriteMutexes.Add(inMutex);
}

void gRegisterUnlockMutex(const ReadWriteMutex* inMutex)
{
	gAssert(gLockedReadWriteMutexes.Contains(inMutex), "Mutex is not locked by this thread");
	gLockedReadWriteMutexes.SwapRemove(gLockedReadWriteMutexes.Find(inMutex));
}

#endif

void Mutex::Lock()
{
    IF_ASSERTS(gRegisterLockMutex(this); )

	mMutex.lock();
}

void Mutex::Unlock()
{
	IF_ASSERTS(gRegisterUnlockMutex(this); )

    mMutex.unlock();
}

void ReadWriteMutex::WriteLock()
{
	IF_ASSERTS(gRegisterLockMutex(this); )

	mMutex.lock();
}

void ReadWriteMutex::WriteUnlock()
{
	IF_ASSERTS(gRegisterUnlockMutex(this); )

	mMutex.unlock();
}

void ReadWriteMutex::ReadLock()
{
	IF_ASSERTS(gRegisterLockMutex(this); )

	mMutex.lock_shared();
}

void ReadWriteMutex::ReadUnlock()
{
	IF_ASSERTS(gRegisterUnlockMutex(this); )

	mMutex.unlock_shared();
}
