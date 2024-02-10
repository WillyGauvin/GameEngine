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
		GameObject* ObjectA = contact->GetFixtureA()->GetBody()->GetUserData().pGameObject;
		GameObject* ObjectB = contact->GetFixtureB()->GetBody()->GetUserData().pGameObject;

		b2WorldManifold manifold;
		contact->GetWorldManifold(&manifold);

		vec2 normal(manifold.normal.x, manifold.normal.y);

		vec2 CollisionNormalA = normal;
		vec2 CollisionNormalB = normal * -1;

		vec2 VelocityA = vec2(contact->GetFixtureA()->GetBody()->GetLinearVelocity().x, contact->GetFixtureA()->GetBody()->GetLinearVelocity().y);
		vec2 VelocityB = vec2(contact->GetFixtureB()->GetBody()->GetLinearVelocity().x, contact->GetFixtureB()->GetBody()->GetLinearVelocity().y);

		float speedA = VelocityA.Length();
		float speedB = VelocityB.Length();

		Event* pEvent = new CollisionEvent(ObjectA, ObjectB, CollisionNormalA, CollisionNormalB, speedA, speedB);

		m_pEventManager->AddEvent(pEvent);
	}
}
