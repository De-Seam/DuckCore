#include <DuckCore/Core/Core.h>

#include <DuckCore/Threads/Thread.h>

namespace DC
{
void Core::sStartup()
{
	SetCurrentThreadAsMainThread();
}
}
