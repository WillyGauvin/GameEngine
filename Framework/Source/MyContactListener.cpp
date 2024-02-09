#include "MyContactListener.h"
#include "Objects/GameObject.h"

namespace fw
{
	MyContactListener::MyContactListener(EventManager* pManager) :
		m_pEventManager(pManager)
	{
	}

	MyContactListener::~MyContactListener()
	{
	}

	void MyContactListener::BeginContact(b2Contact* contact)
	{
		GameObject* Body1 = contact->GetFixtureA()->GetBody()->GetUserData().pGameObject;
		GameObject* Body2 = contact->GetFixtureB()->GetBody()->GetUserData().pGameObject;

		Event* pEvent = new CollisionEvent(Body1, Body2);

		m_pEventManager->AddEvent(pEvent);
	}
}
