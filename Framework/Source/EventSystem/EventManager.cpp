#include "EventManager.h"
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
			m_Queue.pop();

			m_pGame->OnEvent(pEvent);
			delete pEvent;
		
		}
	}
}

