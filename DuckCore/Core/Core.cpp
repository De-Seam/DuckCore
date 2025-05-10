#include <DuckCore/Core/Core.h>

#include <DuckCore/Events/EventManager.h>
#include <DuckCore/Managers/CommandLineArgumentsManager.h>
#include <DuckCore/Managers/Managers.h>
#include <DuckCore/Memory/Memory.h>
#include <DuckCore/Threads/Thread.h>
#include <DuckCore/UnitTests/UnitTests.h>

namespace DC
{
void Core::sStartup(int aArgumentCount, char* aArgumentValues[])
{
	SetCurrentThreadAsMainThread();

	Managers::sAdd(New<CommandLineArgumentsManager>(aArgumentCount, aArgumentValues));
	Managers::sAdd(New<EventManager>());

#ifndef _SHIP
	if (Get<CommandLineArgumentsManager>().HasArgument("enable_unit_tests"))
		UnitTests::RunAllTests();
#endif
}
}
