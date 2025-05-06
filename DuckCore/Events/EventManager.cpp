#include <DuckCore/Events/EventManager.h>

namespace DC
{
void EventManager::UnregisterEventHandle(const EventHandle& inEventHandle)
{
	ScopedMutexRecursiveLock lock(mMutex);

	gAssert(!mCurrentlyBroadcastingEvents.Contains(&taEventType::sGetRTTI()), "Cant unregister event listeners while broadcasting that specific event.");

	const RTTI* rtti = &inEventHandle.mEventRTTI;
	Array<EventHandle*>& event_callbacks = mEventCallbacks[rtti];

	const int index = event_callbacks.Find(&inEventHandle);

	gAssert(index != -1);

	event_callbacks.SwapRemove(index);
}
}