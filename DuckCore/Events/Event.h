#pragma once
#include <DuckCore/RTTI/RTTIClass.h>

/*
Example usage:
class WindowEvent : public Event
{
	RTTI_EVENT(WindowEvent, Event)
};

class WindowCloseEvent : public WindowEvent
{
	RTTI_EVENT(WindowCloseEvent, WindowEvent)
};
*/
#define RTTI_EVENT(inClassName, inBaseClassName) \
	RTTI_CLASS(inClassName, inBaseClassName) \
	inline static const EventTypeID sManagerTypeID = EventTypeID::sNew();


namespace DC
{
using EventTypeID = TypeID<class Event>;

class Event : public RTTIClass
{
	RTTI_CLASS(Event, RTTIClass)
public:
};
}
