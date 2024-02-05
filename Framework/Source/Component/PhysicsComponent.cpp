#include "PhysicsComponent.h"
#include "Component/TransformComponent.h"
namespace fw
{
	PhysicsComponent::PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic) : Component(pGameObject)
	{
        b2BodyDef bodyDef;
        if (isDynamic == true)
        {
            bodyDef.type = b2_dynamicBody;
        }
        else
        {
            bodyDef.type = b2_kinematicBody;
        }

        bodyDef.position = b2Vec2(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y);
        m_pBody = m_pWorld->CreateBody(&bodyDef);

	}

	PhysicsComponent::~PhysicsComponent()
	{

	}

    void PhysicsComponent::SetCircle(float radius)
    {
        b2CircleShape circle;
        circle.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        fixtureDef.density = 1.0f;
        m_pBody->CreateFixture(&fixtureDef);

    }
    void PhysicsComponent::SetBox(vec2 size)
    {
        b2PolygonShape box;
        box.SetAsBox(size.x, size.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 1.0f;
        m_pBody->CreateFixture(&fixtureDef);
    }
   
    void PhysicsComponent::SetPoly(const b2Vec2* points, int32 count)
    {
        b2PolygonShape poly;
        poly.Set(points, count);

    }
}