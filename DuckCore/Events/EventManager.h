#pragma once
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/UniquePtr.h>
#include <DuckCore/Events/Event.h>
#include <DuckCore/Manager/Manager.h>
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

protected:
	virtual void Call(Event& ioEvent) override { mOnEventFunction(*gStaticCast<taEventType*>(&ioEvent)); }

private:
	EventHandle(std::function<void(taEventType&)> inOnEventFunction, EventManager& inEventManager) :
		mOnEventFunction(Move(inOnEventFunction)),
		mEventManager(&inEventManager)
	{}

	std::function<void(taEventType&)> mOnEventFunction;
	EventManager* mEventManager = nullptr;

	friend class EventManager;
};

class EventManager : public Manager
{
	MANAGER_BASE_CLASS(EventManager)
public:
	template<typename taEventType>
	UniquePtr<EventHandle<taEventType>> AddEventListener(std::function<void(taEventType&)> inFunction);

	template<typename taEventType>
	void SendEvent(taEventType& ioEvent);

private:
	template<typename taEventType>
	void UnregisterEventHandle(const EventHandle<taEventType>& inEventHandle);

	HashMap<const RTTI*, Array<EventHandleBase*>> mEventCallbacks;

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

	UniquePtr<EventHandle<taEventType>> handle = MakeUnique<EventHandle<taEventType>>();
	handle->mOnEventFunction = inFunction;
	handle->mEventManager = this;

	const RTTI* rtti = &taEventType::sGetRTTI();
	mEventCallbacks[rtti].Add(handle);

	return handle;
}

template<typename taEventType>
void EventManager::SendEvent(taEventType& ioEvent)
{
	gAssert(gIsMainThread());

	const RTTI* rtti = &taEventType::sGetRTTI();
	Array<EventHandleBase*>& event_callbacks = mEventCallbacks[rtti];

	for (EventHandleBase* handle : event_callbacks)
		handle->Call(ioEvent);
}

template<typename taEventType>
void EventManager::UnregisterEventHandle(const EventHandle<taEventType>& inEventHandle)
{
	gAssert(gIsMainThread());

	const RTTI* rtti = &taEventType::sGetRTTI();
	Array<EventHandleBase*>& event_callbacks = mEventCallbacks[rtti];

	const int index = event_callbacks.Find(&inEventHandle);

	gAssert(index != -1);

	event_callbacks.SwapRemove(index);
}
}
