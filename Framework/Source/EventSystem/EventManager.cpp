#include "EventManager.h"
#include "EventListener.h"
namespace fw
{
	EventManager::EventManager(GameCore* Game) :
		m_pGame(Game)
	{

	}

	EventManager::~EventManager()
	{

	}

	void EventManager::AddEvent(Event* pEvent)
	{
		m_Queue.push(pEvent);
	}

	void EventManager::ProcessEvents()
	{
		while (m_Queue.size() != 0)
		{
			Event* pEvent = m_Queue.front();

			std::vector<EventListener*>& list = m_Listeners[pEvent->GetType()];

			for (EventListener* listener : list)
			{
				listener->ExecuteEvent(pEvent);
			}

			m_Queue.pop();

			delete pEvent;
		
		}
	}
	void EventManager::RegisterListener(EventType event, EventListener* pEventListener)
	{
		m_Listeners[event].push_back(pEventListener);
		int i = 0;
	}
}

