#include <DuckCore/Threads/Thread.h>

#include <DuckCore/Core/Assert.h>
#include <DuckCore/Threads/Atomic.h>

#include <thread>

namespace DC
{
int gMainThreadID = -1;

void SetCurrentThreadAsMainThread()
{
	gMainThreadID = GetThreadID();
}

int GetThreadID()
{
	static Atomic<int> sNextThreadID = 0;
	static thread_local int sThreadID = sNextThreadID++;

	return sThreadID;
}

bool IsMainThread()
{
	gAssert(gMainThreadID != -1, "Main thread ID not set.");
	return GetThreadID() == gMainThreadID;
}
}
