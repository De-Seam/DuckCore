#pragma once
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/UniquePtr.h>
#include <DuckCore/Events/Event.h>
#include <DuckCore/Managers/Manager.h>
#include <DuckCore/Threads/Thread.h>

namespace DC
{
class EventManager;

class EventHandleBase : public NoCopy, public NoMove
{
public:
	virtual ~EventHandleBase() = default;
protected:
	virtual void Call(Event& ioEvent) = 0;

	friend class EventManager;
};

template<typename taEventType>
class EventHandle final : public EventHandleBase
{
public:
	virtual ~EventHandle() override;
	EventHandle() = delete;
	EventHandle(std::function<void(taEventType&)> inOnEventFunction, EventManager& inEventManager) :
		mOnEventFunction(Move(inOnEventFunction)),
		mEventManager(&inEventManager)
	{}

protected:
	virtual void Call(Event& ioEvent) override { mOnEventFunction(*gStaticCast<taEventType*>(&ioEvent)); }

private:
	std::function<void(taEventType&)> mOnEventFunction;
	EventManager* mEventManager = nullptr;

	friend class EventManager;
};

class EventManager : public Manager
{
	MANAGER_BASE_CLASS(EventManager)
public:
	template<typename taEventType> [[nodiscard]]
	UniquePtr<EventHandle<taEventType>> AddEventListener(std::function<void(taEventType&)> inFunction);

	template<typename taEventType>
	void SendEvent(taEventType& ioEvent);

private:
	template<typename taEventType>
	void UnregisterEventHandle(const EventHandle<taEventType>& inEventHandle);

	HashMap<const RTTI*, Array<EventHandleBase*>> mEventCallbacks;
	IF_ASSERTS(Array<const RTTI*> mCurrentlyBroadcastingEvents;) // Asserts-only, array of events we are currently broadcasting using SendEvent.

	template<typename taEventType>
	friend class EventHandle;
};

template<typename taEventType>
EventHandle<taEventType>::~EventHandle()
{
	mEventManager->UnregisterEventHandle(*this);
}

template<typename taEventType>
UniquePtr<EventHandle<taEventType>> EventManager::AddEventListener(std::function<void(taEventType&)> inFunction)
{
	gAssert(gIsMainThread());
	gAssert(!mCurrentlyBroadcastingEvents.Contains(&taEventType::sGetRTTI()), "Cant register event listeners while broadcasting that specific event.");

	UniquePtr<EventHandle<taEventType>> handle = MakeUnique<EventHandle<taEventType>>(inFunction, *this);

	const RTTI* rtti = &taEventType::sGetRTTI();
	mEventCallbacks[rtti].Add(handle);

	return handle;
}

template<typename taEventType>
void EventManager::SendEvent(taEventType& ioEvent)
{
	gAssert(gIsMainThread());

	const RTTI* rtti = &taEventType::sGetRTTI();

	gAssert(!mCurrentlyBroadcastingEvents.Contains(rtti), "Cant send event while broadcasting that same event.");
	IF_ASSERTS(mCurrentlyBroadcastingEvents.Add(rtti);)

	Array<EventHandleBase*>& event_callbacks = mEventCallbacks[rtti];

	for (EventHandleBase* handle : event_callbacks)
		handle->Call(ioEvent);

	IF_ASSERTS(mCurrentlyBroadcastingEvents.RemoveFirstIf([rtti](const RTTI* aRTTI) { return rtti == aRTTI; });)
}

template<typename taEventType>
void EventManager::UnregisterEventHandle(const EventHandle<taEventType>& inEventHandle)
{
	gAssert(gIsMainThread());
	gAssert(!mCurrentlyBroadcastingEvents.Contains(&taEventType::sGetRTTI()), "Cant unregister event listeners while broadcasting that specific event.");

	const RTTI* rtti = &taEventType::sGetRTTI();
	Array<EventHandleBase*>& event_callbacks = mEventCallbacks[rtti];

	const int index = event_callbacks.Find(&inEventHandle);

	gAssert(index != -1);

	event_callbacks.SwapRemove(index);
}
}
