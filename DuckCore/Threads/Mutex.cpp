#include <DuckCore/Threads/Mutex.h>

// DuckCore includes
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Core/Assert.h>

namespace DC
{
#ifdef _ASSERTS

THREADLOCAL Array<const MutexBase*> gLockedMutexes;

void gRegisterLockMutex(const MutexBase* inMutex)
{
	gAssert(!gLockedMutexes.Contains(inMutex), "Mutex is already locked by same thread");
	gLockedMutexes.Add(inMutex);
}

void gRegisterUnlockMutex(const MutexBase* inMutex)
{
	gAssert(gLockedMutexes.Contains(inMutex), "Mutex is not locked by this thread");
	gLockedMutexes.SwapRemove(gLockedMutexes.Find(inMutex));
}

bool MutexBase::IsLockedByCurrentThread() const 
{ 
	return gLockedMutexes.Contains(this); 
}

#endif

void Mutex::Lock()
{
	IF_ASSERTS(gRegisterLockMutex(this); )

	mMutex.lock();
}

bool Mutex::TryLock() 
{
	const bool result = mMutex.try_lock();
#ifdef _ASSERTS
	if (result)
		gRegisterLockMutex(this);
#endif
	return result;
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

bool ReadWriteMutex::TryWriteLock() 
{
	const bool result = mMutex.try_lock();
#ifdef _ASSERTS
	if (result)
		gRegisterLockMutex(this);
#endif
	return result;
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

bool ReadWriteMutex::TryReadLock() 
{
	const bool result = mMutex.try_lock_shared();
#ifdef _ASSERTS
	if (result)
		gRegisterLockMutex(this);
#endif
	return result;
}

void ReadWriteMutex::ReadUnlock()
{
	IF_ASSERTS(gRegisterUnlockMutex(this); )

	mMutex.unlock_shared();
}
}
