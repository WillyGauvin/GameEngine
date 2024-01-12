#pragma once
#include "CoreHeaders.h"
#include "Events.h"
#include "GameCore.h"

namespace fw
{
	class EventManager
	{
	public:
		EventManager(GameCore* Game);
		virtual ~EventManager();

		void AddEvent(Event* pEvent);
		void ProcessEvents(); 
		
	protected:
		std::queue<Event*> m_Queue;
		GameCore* m_pGame;
	};
}