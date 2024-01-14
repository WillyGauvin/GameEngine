#pragma once
#include "CoreHeaders.h"
#include "Events.h"
#include "GameCore.h"

namespace fw
{
	class EventListener
	{
	public:
		virtual void ExecuteEvent(Event* pEvent) = 0;
	};
}