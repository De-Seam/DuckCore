#include <DuckCore/Core/Core.h>

#include <DuckCore/Events/EventManager.h>
#include <DuckCore/Managers/Managers.h>
#include <DuckCore/Threads/Thread.h>

namespace DC
{
void Core::sStartup()
{
	SetCurrentThreadAsMainThread();

	Managers::sAdd(new EventManager);
}
}
