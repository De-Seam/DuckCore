#pragma once
#include <DuckCore/RTTI/RTTIClass.h>

/*
Example usages:
class EventManager : public Manager
{
	MANAGER_BASE_CLASS(EventManager)
};

class EventManagerGame : public EventManager
{
	RTTI_CLASS(EventManagerGame, EventManager)
};
*/
#define MANAGER_BASE_CLASS(inClassName) \
	RTTI_CLASS(inClassName, Manager) \
public:\
	inline static const DC::ManagerTypeID sManagerTypeID = DC::ManagerTypeID::sNew(); \
private:

namespace DC
{
using ManagerTypeID = TypeID<class Manager>;

class Manager : public RTTIClass
{
	RTTI_CLASS(Manager, RTTIClass)
public:

private:
};
}