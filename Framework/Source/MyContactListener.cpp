#include "MyContactListener.h"

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
		contact->GetFixtureA()->GetBody()->GetUserData().pGameObject;
	}
}
