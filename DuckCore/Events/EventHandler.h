#pragma once
#include <DuckCore/Containers/UniquePtr.h>
#include <DuckCore/Events/EventHandle.h>
#include <DuckCore/Events/EventManager.h>
#include <DuckCore/Managers/Managers.h>

#define EVENT_HANDLER(aEVENT, aFUNCTION) DC::UniquePtr<DC::EventHandle> m##aFUNCTION##Handler = DC::Get<DC::EventManager>().RegisterEventListener<aEVENT>([this](aEVENT& aEvent) { this->aFUNCTION(aEvent); });