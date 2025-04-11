#include "PhysicsComponent.h"
#include "Component/TransformComponent.h"
#include "SceneSystem/Scene.h"
#include "Component/ComponentManager.h"
#include "Jolt/Physics/Body/Body.h"

namespace fw
{
    PhysicsComponent::PhysicsComponent(PhysicsLibrary libType, GameObject* pGameObject, bool isDynamic = true) : Component(pGameObject)
    {
        m_pBox2DWorld = pGameObject->GetScene()->GetComponentManager()->GetBox2DWorld();
        m_pJoltWorld = pGameObject->GetScene()->GetComponentManager()->GetJoltWorld();

        TransformComponent* transform = pGameObject->GetTransformComponent();

        if (libType == PhysicsLibrary::Box2D)
        {
            b2BodyDef bodyDef;

            bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_kinematicBody;

            bodyDef.position = b2Vec2(transform->m_position.x, transform->m_position.y);
            bodyDef.angle = -1.0f * degreesToRads(transform->m_rotation.z);

            m_pBox2DBody = m_pBox2DWorld->CreateBody(&bodyDef);
            m_pBox2DBody->GetUserData().pGameObject = pGameObject;
        }
        else if (libType == PhysicsLibrary::Jolt)
        {
            m_pJoltBody = fw::CreateMeshJoltBody(m_pJoltWorld->m_pWorld, transform->m_position, transform->m_rotation, transform->m_scale, isDynamic, 1.0f, pGameObject);
        }
    }

    void PhysicsComponent::SetMask(uint16 profile, uint16 mask)
    {
        b2Filter filter;
        filter.categoryBits = profile;
        filter.maskBits = mask;

        for (b2Fixture* f = m_pBox2DBody->GetFixtureList(); f; f = f->GetNext())
        {
            f->SetFilterData(filter);
        }
    }

	PhysicsComponent::~PhysicsComponent()
	{
        m_pBox2DWorld->DestroyBody(m_pBox2DBody);
        DestroyJoltBody(m_pJoltWorld->m_pWorld, m_pJoltBody);
	}

    void PhysicsComponent::Reset()
    {
        m_pBox2DBody->SetAngularVelocity(0.0f);
        m_pBox2DBody->SetLinearVelocity(b2Vec2(0,0));

        b2Vec2 position = b2Vec2(m_pGameObject->GetTransformComponent()->m_position.x, m_pGameObject->GetTransformComponent()->m_position.y);
        float rotation = -1.0f * degreesToRads(m_pGameObject->GetTransformComponent()->m_rotation.z);

        m_pBox2DBody->SetTransform(position, rotation);
    }

    void PhysicsComponent::AddLinearImpulse(vec2 impulse)
    {
        m_pBox2DBody->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), m_pBox2DBody->GetWorldCenter(), true);
    }

    void PhysicsComponent::AddAngularImpulse(float impulse)
    {
        m_pBox2DBody->ApplyAngularImpulse(impulse, true);
    }

    void PhysicsComponent::AddForce(vec2 force)
    {
        m_pBox2DBody->ApplyForce(b2Vec2(force.x, force.y), m_pBox2DBody->GetWorldCenter(), true);
    }

    void PhysicsComponent::AddForce(vec2 force, vec2 offset)
    {
        m_pBox2DBody->ApplyForce(b2Vec2(force.x, force.y), m_pBox2DBody->GetWorldCenter() + b2Vec2(offset.x, offset.y), true);
    }

    void PhysicsComponent::AddUpForce(float force, vec2 offset)
    {
        vec2 UpVector = vec2(cos(m_pBox2DBody->GetAngle() + PI/2), sin(m_pBox2DBody->GetAngle() + PI/2)).Normalize();
        m_pBox2DBody->ApplyForce(b2Vec2(UpVector.x * force, UpVector.y * force), m_pBox2DBody->GetWorldCenter() + b2Vec2(offset.x, offset.y), true);
    }

    void PhysicsComponent::AddUpForce(float force)
    {
        vec2 UpVector = vec2(cos(m_pBox2DBody->GetAngle() + PI/2), sin(m_pBox2DBody->GetAngle() + PI/2)).Normalize();
        m_pBox2DBody->ApplyForce(b2Vec2(UpVector.x * force, UpVector.y * force), m_pBox2DBody->GetWorldCenter(), true);
    }

    void PhysicsComponent::UpdateBody()
    {
        vec3 rotation = vec3(0.0f,0.0f,-1.0f * radsToDegrees(m_pBox2DBody->GetAngle()));
        vec3 position = vec3(m_pBox2DBody->GetTransform().p.x, m_pBox2DBody->GetTransform().p.y, 0.0f);
        m_pGameObject->GetTransformComponent()->UpdatePosition(position);
        m_pGameObject->GetTransformComponent()->UpdateRotation(rotation);
    }
    
    void PhysicsComponent::SetCircle(bool isProjectile)
    {
        b2CircleShape circle;
        circle.m_radius = m_pGameObject->GetTransformComponent()->m_scale.x * 2;

        m_fixtureDef.shape = &circle;
        m_fixtureDef.density = 1.0f;
        m_pBody->CreateFixture(&m_fixtureDef);
        m_pBody->SetBullet(isProjectile);
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

    void PhysicsComponent::SetBox(vec2 scale)
    {
        b2PolygonShape box;

        box.SetAsBox(scale.x / 2, scale.y / 2);

        m_fixtureDef.shape = &box;
        m_fixtureDef.density = 1.0f;
        m_pBody->CreateFixture(&m_fixtureDef);
    }
   
    void PhysicsComponent::SetPoly(const b2Vec2* points, int32 count)
    {
        b2PolygonShape dynamicPolygon;
  

        dynamicPolygon.Set(points, count);
        m_fixtureDef.shape = &dynamicPolygon;
        m_fixtureDef.density = 1.0f;

        m_pBody->CreateFixture(&m_fixtureDef);
    }
    void PhysicsComponent::SetTriangle()
    {
        b2PolygonShape dynamicPolygon;
  

        b2Vec2 triangleVertices[3] =
        {
            b2Vec2(0.0f, 0.5f * m_pGameObject->GetTransformComponent()->m_scale.y),
            b2Vec2(-0.5f * m_pGameObject->GetTransformComponent()->m_scale.x ,-0.5f * m_pGameObject->GetTransformComponent()->m_scale.y),
            b2Vec2(0.5f * m_pGameObject->GetTransformComponent()->m_scale.x,-0.5f * m_pGameObject->GetTransformComponent()->m_scale.y)
        };

        dynamicPolygon.Set(triangleVertices, 3);
        m_fixtureDef.shape = &dynamicPolygon;
        m_fixtureDef.density = 1.0f;

        m_pBody->CreateFixture(&m_fixtureDef);
    }
    void PhysicsComponent::SetSensor()
    {
        b2CircleShape circle;
        circle.m_radius = m_pGameObject->GetTransformComponent()->m_scale.x * 2;

        m_fixtureDef.shape = &circle;
        m_fixtureDef.density = 1.0f;
        m_fixtureDef.isSensor = true;
        m_pBody->CreateFixture(&m_fixtureDef);
    }
    void PhysicsComponent::SetLineCensor()
    {
        b2PolygonShape box;
        vec3 scale = m_pGameObject->GetTransformComponent()->m_scale;
        vec2 size = vec2(scale.x, scale.y);
        box.SetAsBox(size.x, size.y);

        m_fixtureDef.shape = &box;
        m_fixtureDef.density = 1.0f;
        m_fixtureDef.isSensor = true;
        m_pBody->CreateFixture(&m_fixtureDef);

    }
    void PhysicsComponent::DestoryJoint()
    {
        if (m_pJoint != nullptr)
        {
            m_pWorld->DestroyJoint(m_pJoint);
            m_pJoint = nullptr;
        }
    }

    void PhysicsComponent::CreateWeldJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor)
    {
        b2WeldJointDef jointDef;
        jointDef.bodyA = m_pBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBody;
        jointDef.localAnchorA = b2Vec2(thisObjectAnchor.x, thisObjectAnchor.y);
        jointDef.localAnchorB = b2Vec2(otherObjectAnchor.x, otherObjectAnchor.y);
        jointDef.collideConnected = false;
        m_pWorld->CreateJoint(&jointDef);
    }
}