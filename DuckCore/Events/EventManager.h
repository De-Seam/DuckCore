#pragma once
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/UniquePtr.h>
#include <DuckCore/Events/Event.h>
#include <DuckCore/Events/EventHandle.h>
#include <DuckCore/Managers/Manager.h>
#include <DuckCore/Threads/Mutex.h>
#include <DuckCore/Threads/ScopedMutex.h>
#include <DuckCore/Threads/Thread.h>

namespace DC
{
class EventManager : public Manager
{
	MANAGER_BASE_CLASS(EventManager)
public:
	template<typename taEventType> [[nodiscard]]
	UniquePtr<EventHandle> RegisterEventListener(std::function<void(taEventType&)> inFunction);

	template<typename taEventType>
	void SendEvent(taEventType& ioEvent);

private:
	void UnregisterEventHandle(const EventHandle& inEventHandle);

	HashMap<const RTTI*, Array<EventHandle*>> mEventCallbacks;
	IF_ASSERTS(Array<const RTTI*> mCurrentlyBroadcastingEvents;) // Asserts-only, array of events we are currently broadcasting using SendEvent.

	RecursiveMutex mMutex;

	friend class EventHandle;
};

template<typename taEventType>
UniquePtr<EventHandle> EventManager::RegisterEventListener(std::function<void(taEventType&)> inFunction)
{
	UniquePtr<EventHandle> handle = MakeUnique<EventHandle>([inFunction](void* inArgument) { inFunction(*gReinterpretCast<taEventType*>(inArgument)); }, taEventType::sGetRTTI(), *this);

	ScopedMutexRecursiveLock lock(mMutex);

	gAssert(!mCurrentlyBroadcastingEvents.Contains(&taEventType::sGetRTTI()), "Cant register event listeners while broadcasting that specific event.");

	const RTTI* rtti = &taEventType::sGetRTTI();
	Array<EventHandle*>& event_handles = mEventCallbacks[rtti];
	event_handles.Add(handle);

	return handle;
}

template<typename taEventType>
void EventManager::SendEvent(taEventType& ioEvent)
{
	const RTTI* rtti = &taEventType::sGetRTTI();

	ScopedMutexRecursiveLock lock(mMutex);

	gAssert(!mCurrentlyBroadcastingEvents.Contains(rtti), "Cant send event while broadcasting that same event.");
	IF_ASSERTS(mCurrentlyBroadcastingEvents.Add(rtti);)

	Array<EventHandle*>& event_callbacks = mEventCallbacks[rtti];

	for (EventHandle* handle : event_callbacks)
		handle->Call(ioEvent);

	IF_ASSERTS(mCurrentlyBroadcastingEvents.RemoveFirstIf([rtti](const RTTI* aRTTI) { return rtti == aRTTI; });)
}
}
