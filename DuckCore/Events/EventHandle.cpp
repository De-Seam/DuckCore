#include <DuckCore/Events/EventHandle.h>

#include <DuckCore/Events/EventManager.h>

namespace DC
{
EventHandle::~EventHandle()
{
    mEventManager.UnregisterEventHandle(*this);
}
}