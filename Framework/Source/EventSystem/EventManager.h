#pragma once
#include "CoreHeaders.h"
#include "Events.h"
#include "GameCore.h"

namespace fw
{

	class EventListener;

	class EventManager
	{
	public:
		EventManager(GameCore* Game);
		virtual ~EventManager();

		void AddEvent(Event* pEvent);
		void ProcessEvents(); 
		void RegisterListener(EventType event, EventListener* pEventListener);
		
	protected:
		std::queue<Event*> m_Queue;
		GameCore* m_pGame;
		std::map<EventType, std::vector<EventListener*>> m_Listeners;
	};
}