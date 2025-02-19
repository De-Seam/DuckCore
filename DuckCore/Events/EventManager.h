#pragma once
#include <DuckCore/Containers/Array.h>
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
		mOnEventFunction(gMove(inOnEventFunction)),
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

	Array<Array<EventHandleBase*>> mEventCallbacks;

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

	const EventTypeID& event_type_id = taEventType::sManagerTypeID;
	if (!mEventCallbacks.IsValidIndex(event_type_id))
		mEventCallbacks.Resize(event_type_id + 1);

	mEventCallbacks[event_type_id].Add(inFunction);

	UniquePtr<EventHandle<taEventType>> handle = gMakeUnique<EventHandle<taEventType>>();
	handle->mOnEventFunction = inFunction;
	handle->mEventManager = this;
	return handle;
}

template<typename taEventType>
void EventManager::SendEvent(taEventType& ioEvent)
{
	gAssert(gIsMainThread());

	const EventTypeID& event_type_id = taEventType::sManagerTypeID;
	if (!mEventCallbacks.IsValidIndex(event_type_id))
		return;

	for (EventHandleBase* handle : mEventCallbacks[event_type_id])
		handle->Call(ioEvent);
}

template<typename taEventType>
void EventManager::UnregisterEventHandle(const EventHandle<taEventType>& inEventHandle)
{
	gAssert(gIsMainThread());

	const EventTypeID& event_type_id = taEventType::sManagerTypeID;
	const int index = mEventCallbacks[event_type_id].Find(&inEventHandle);

	gAssert(index != -1);

	mEventCallbacks[event_type_id].SwapRemove(index);
}
}
