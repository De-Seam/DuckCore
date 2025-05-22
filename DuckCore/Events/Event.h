#pragma once
#include <DuckCore/RTTI/RTTIClass.h>
#include <DuckCore/Utilities/TypeID.h>

/*
Example usage:
class WindowEvent : public Event
{
	RTTI_EVENT_CLASS(WindowEvent, Event)
};

class WindowCloseEvent : public WindowEvent
{
	RTTI_EVENT_CLASS(WindowCloseEvent, WindowEvent)
};
*/
#define RTTI_EVENT_CLASS(inClassName, inBaseClassName) \
	RTTI_CLASS(inClassName, inBaseClassName) \
	inline static const DC::EventTypeID sManagerTypeID = DC::EventTypeID::sNew();

namespace DC
{
using EventTypeID = TypeID<class Event>;

class Event : public RTTIClass
{
	RTTI_CLASS(Event, RTTIClass)
public:
};

class ShutdownEvent : public Event
{
	RTTI_EVENT_CLASS(ShutdownEvent, Event)
};
}
