#pragma once
#include "EventSystem/EventManager.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"

class EventManager;

namespace fw
{
	class MyContactListener : public b2ContactListener
	{
	public:
		MyContactListener(EventManager* pManager);
		virtual ~MyContactListener() override;

		virtual void BeginContact(b2Contact* contact) override;
	protected:
		EventManager* m_pEventManager = nullptr;
	};
}
