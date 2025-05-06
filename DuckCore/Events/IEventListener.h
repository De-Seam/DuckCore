#pragma once
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Events/EventManager.h>
#include <DuckCore/Managers/Managers.h>

namespace DC
{
class EventHandle;

class IEventListener
{
protected:
    template <typename tEventType>
    void RegisterEventListener(std::function<void(tEventType&)> aFunction);

private:
    DC::Array<EventHandle*> mRegisteredEventHandles;
};

template <typename tEventType>
void IEventListener::RegisterEventListener(std::function<void(tEventType&)> aFunction)
{
    UniquePtr<EventHandle> event_handle = Get<EventManager>().RegisterEventListener<tEventType>(aFunction);
    mRegisteredEventHandles.Add(Move(event_handle));
}
}