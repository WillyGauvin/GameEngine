#include "MyContactListener.h"

namespace fw
{
	MyContactListener::MyContactListener(EventManager* pManager)
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
