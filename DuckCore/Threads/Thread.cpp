#include <DuckCore/Threads/Thread.h>

#include <DuckCore/Threads/Atomic.h>

#include <thread>

namespace DC
{
int gGetThreadID()
{
	static Atomic<int> sNextThreadID = 0;
	static thread_local int sThreadID = sNextThreadID++;

	return sThreadID;
}

bool gIsMainThread()
{
	return gGetThreadID() == 0;
}
}
