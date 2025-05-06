#pragma once
#include <DuckCore/Utilities/NoCopy.h>
#include <DuckCore/Utilities/Utilities.h>

#include <functional>

namespace DC
{
class Event;
class RTTI;
class EventManager;

class EventHandle final : public NoCopy, public NoMove
{
public:
	~EventHandle();
	EventHandle() = delete;

	EventHandle(std::function<void(void*)> inOnEventFunction, const RTTI& inEventRTTI, EventManager& inEventManager) :
	mOnEventFunction(Move(inOnEventFunction)),
	mEventRTTI(inEventRTTI),
	mEventManager(inEventManager)
	{}
	
private:
	void Call(Event& ioEvent) { mOnEventFunction(&ioEvent); }

	std::function<void(void*)> mOnEventFunction;
	const RTTI& mEventRTTI;
	EventManager& mEventManager;

	friend class EventManager;
};
}