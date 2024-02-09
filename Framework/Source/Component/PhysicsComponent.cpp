#include "PhysicsComponent.h"
#include "Component/TransformComponent.h"
namespace fw
{


	PhysicsComponent::PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic, PhysicsCategories PhysicsCategory) : Component(pGameObject),
        m_pWorld(pWorld)
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

        bodyDef.position = b2Vec2(m_pGameObject->GetTransformComponent()->m_position.x, m_pGameObject->GetTransformComponent()->m_position.y);
        m_pBody = m_pWorld->CreateBody(&bodyDef);
        m_pBody->GetUserData().pGameObject = pGameObject;


        //
     /*   PhysicsCategory_Default
            PhysicsCategory_Wall =
            PhysicsCategory_Bumper
            PhysicsCategory_Paddle
            PhysicsCategory_Ball =*/






        switch (PhysicsCategory)
        {
             case(PhysicsCategories::PhysicsCategory_Default):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Default);

                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Wall) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Bumper) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Paddle) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Default);
                 break;
             }
             case(PhysicsCategories::PhysicsCategory_Wall):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Wall);
                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Default) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);
                 break;

             }
             case(PhysicsCategories::PhysicsCategory_Bumper):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Bumper);
                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Default) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);
                 break;

             }
             case(PhysicsCategories::PhysicsCategory_Paddle):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Paddle);
                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Default) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);
                 break;

             }
             case(PhysicsCategories::PhysicsCategory_Ball):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);
                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Wall) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Bumper) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Paddle) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Default);
                 break;

             }
        }
	}

	PhysicsComponent::~PhysicsComponent()
	{

	}

    void PhysicsComponent::UpdateBody()
    {
        //b2Vec2 rotation = m_pBody->GetTransform().q.GetXAxis();
        vec3 position = vec3(m_pBody->GetTransform().p.x, m_pBody->GetTransform().p.y, 0);
        m_pGameObject->GetTransformComponent()->UpdatePosition(position);
    }

    void PhysicsComponent::SetCircle()
    {
        b2CircleShape circle;
        circle.m_radius = m_pGameObject->GetTransformComponent()->m_scale.x * 2;

        m_fixtureDef.shape = &circle;
        m_fixtureDef.density = 1.0f;
        m_pBody->CreateFixture(&m_fixtureDef);

    }
    void PhysicsComponent::SetBox()
    {
        b2PolygonShape box;
        vec3 scale = m_pGameObject->GetTransformComponent()->m_scale;
        vec2 size = vec2(scale.x, scale.y);
        box.SetAsBox(size.x / 2, size.y / 2);

        m_fixtureDef.shape = &box;
        m_fixtureDef.density = 1.0f;
        m_pBody->CreateFixture(&m_fixtureDef);
    }
   
    void PhysicsComponent::SetPoly(const b2Vec2* points, int32 count)
    {
        b2PolygonShape poly;
        poly.Set(points, count);

    }
}