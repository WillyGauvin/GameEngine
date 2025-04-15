#include "PhysicsComponent.h"
#include "SceneSystem/Scene.h"
#include "Component/TransformComponent.h"
#include "Component/ComponentManager.h"

#include "Jolt/Jolt.h"
#include "Jolt/Physics/Body/Body.h"

namespace fw
{
    PhysicsComponent::PhysicsComponent(PhysicsLibrary libType, GameObject* pGameObject, ShapeType type, bool isDynamic, bool isTrigger) : Component(pGameObject),
        m_mode(libType)
    {
        m_pBox2DWorld = pGameObject->GetScene()->GetComponentManager()->GetBox2DWorld();
        m_pJoltWorld = pGameObject->GetScene()->GetComponentManager()->GetJoltWorld();

        TransformComponent* transform = pGameObject->GetTransformComponent();

        if (m_mode == PhysicsLibrary::Box2D)
        {
            b2BodyDef bodyDef;

            bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_kinematicBody;

            bodyDef.position = b2Vec2(transform->m_position.x, transform->m_position.y);
            bodyDef.angle = -1.0f * degreesToRads(transform->m_rotation.z);

            m_pBox2DBody = m_pBox2DWorld->CreateBody(&bodyDef);
            m_pBox2DBody->GetUserData().pGameObject = pGameObject;
        }
        else if (m_mode == PhysicsLibrary::Jolt)
        {
            switch (type)
            {
            case ShapeType::Cube:
                m_pJoltBody = fw::CreateCubeJoltBody(m_pJoltWorld->m_pWorld, transform->m_position, transform->m_rotation, transform->m_scale, isDynamic, 1.0f);
                break;
            case ShapeType::Sphere:
                m_pJoltBody = fw::CreateSphereJoltBody(m_pJoltWorld->m_pWorld, transform->m_position, transform->m_scale.x, isDynamic, 1.0f);
                break;
            case ShapeType::Mesh:
                m_pJoltBody = fw::CreateMeshJoltBody(m_pJoltWorld->m_pWorld, transform->m_position, transform->m_rotation, transform->m_scale, isDynamic, 1.0f, pGameObject);
                break;
            }
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
        if (m_pBox2DBody)
        {
            m_pBox2DWorld->DestroyBody(m_pBox2DBody);
        }
        if (m_pJoltBody)
        {
            DestroyJoltBody(m_pJoltWorld->m_pWorld, m_pJoltBody);
        }
	}

    void PhysicsComponent::Reset()
    {
        if (m_pBox2DBody)
        {
            m_pBox2DBody->SetAngularVelocity(0.0f);
            m_pBox2DBody->SetLinearVelocity(b2Vec2(0, 0));

            b2Vec2 position = b2Vec2(m_pGameObject->GetTransformComponent()->m_position.x, m_pGameObject->GetTransformComponent()->m_position.y);
            float rotation = -1.0f * degreesToRads(m_pGameObject->GetTransformComponent()->m_rotation.z);

            m_pBox2DBody->SetTransform(position, rotation);
        }
        if (m_pJoltBody)
        {
            m_pJoltBody->ResetMotion();
        }
    }

    void PhysicsComponent::AddForce(vec2 force, ForceMode forceMode)
    {
        if (m_mode == PhysicsLibrary::Box2D)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pBox2DBody->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
            }
            else
            {
                m_pBox2DBody->ApplyLinearImpulseToCenter(b2Vec2(force.x, force.y), true);
            }
        }
        else if (m_mode == PhysicsLibrary::Jolt)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pJoltBody->AddForce(JPH::Vec3Arg(force.x, force.y, 0.0f));
            }
            else
            {
                m_pJoltBody->AddImpulse(JPH::Vec3Arg(force.x, force.y, 0.0f));
            }
        }
    }

    void PhysicsComponent::AddForce(vec3 force, ForceMode forceMode)
    {
        if (m_mode == PhysicsLibrary::Box2D)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pBox2DBody->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
            }
            else
            {
                m_pBox2DBody->ApplyLinearImpulseToCenter(b2Vec2(force.x, force.y), true);
            }
        }
        else if (m_mode == PhysicsLibrary::Jolt)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pJoltBody->AddForce(JPH::Vec3Arg(force.x, force.y, force.z));
            }
            else
            {
                m_pJoltBody->AddImpulse(JPH::Vec3Arg(force.x, force.y, force.z));
            }
        }
    }

    void PhysicsComponent::AddForceAtPosition(vec2 force, vec2 pos, ForceMode forceMode)
    {
        if (m_mode == PhysicsLibrary::Box2D)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pBox2DBody->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(pos.x, pos.y), true);
            }
            else
            {
                m_pBox2DBody->ApplyLinearImpulse(b2Vec2(force.x, force.y), b2Vec2(pos.x, pos.y), true);
            }
        }
        else if (m_mode == PhysicsLibrary::Jolt)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pJoltBody->AddForce(JPH::Vec3Arg(force.x, force.y, 0.0f), JPH::RVec3Arg(pos.x, pos.y, 0.0f));
            }
            else
            {
                m_pJoltBody->AddImpulse(JPH::Vec3Arg(force.x, force.y, 0.0f), JPH::RVec3Arg(pos.x, pos.y, 0.0f));
            }
        }
    }

    void PhysicsComponent::AddForceAtPosition(vec3 force, vec2 pos, ForceMode forceMode)
    {
        if (m_mode == PhysicsLibrary::Box2D)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pBox2DBody->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(pos.x, pos.y), true);
            }
            else
            {
                m_pBox2DBody->ApplyLinearImpulse(b2Vec2(force.x, force.y), b2Vec2(pos.x, pos.y), true);
            }
        }
        else if (m_mode == PhysicsLibrary::Jolt)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pJoltBody->AddForce(JPH::Vec3Arg(force.x, force.y, 0.0f), JPH::RVec3Arg(pos.x, pos.y, force.z));
            }
            else
            {
                m_pJoltBody->AddImpulse(JPH::Vec3Arg(force.x, force.y, 0.0f), JPH::RVec3Arg(pos.x, pos.y, force.z));
            }
        }
    }

    /// <summary>
    /// Apply rotational torque to the physics body
    /// </summary>
    /// <param name="torque"> : For BOX2D bodies, only the Z axis will be applied as rotation is locked to that dimension</param>
    /// <param name="forceMode"></param>
    void PhysicsComponent::AddTorque(vec3 torque, ForceMode forceMode)
    {
        if (m_mode == PhysicsLibrary::Box2D)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pBox2DBody->ApplyTorque(torque.z, true);
            }
            else
            {
                m_pBox2DBody->ApplyAngularImpulse(torque.z, true);
            }
        }
        else if (m_mode == PhysicsLibrary::Jolt)
        {
            if (forceMode == ForceMode::Force)
            {
                m_pJoltBody->AddTorque(JPH::Vec3Arg(torque.x, torque.y, torque.z));
            }
            else
            {
                m_pJoltBody->AddAngularImpulse(JPH::Vec3Arg(torque.x, torque.y, torque.z));
            }
        }
    }

    void PhysicsComponent::UpdateBody()
    {
        vec3 position, rotation;
        if (m_mode == PhysicsLibrary::Box2D)
        {
            position = vec3(m_pBox2DBody->GetTransform().p.x, m_pBox2DBody->GetTransform().p.y, 0.0f);
            rotation = vec3(0.0f, 0.0f, -1.0f * radsToDegrees(m_pBox2DBody->GetAngle()));
        }
        else
        {
            position = vec3(m_pJoltBody->GetPosition().GetX(), m_pJoltBody->GetPosition().GetY(), m_pJoltBody->GetPosition().GetZ());
            rotation = vec3(m_pJoltBody->GetRotation().GetX(), m_pJoltBody->GetRotation().GetY(), m_pJoltBody->GetRotation().GetZ());
            rotation *= 360;
        }


        m_pGameObject->GetTransformComponent()->UpdatePosition(position);
        m_pGameObject->GetTransformComponent()->UpdateRotation(rotation);
    }
    
    void PhysicsComponent::SetCircle(bool isProjectile)
    {
        b2CircleShape circle;
        circle.m_radius = m_pGameObject->GetTransformComponent()->m_scale.x * 2;
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        fixtureDef.density = 1.0f;
        m_pBox2DBody->CreateFixture(&fixtureDef);
        m_pBox2DBody->SetBullet(isProjectile);
    }
    void PhysicsComponent::SetBox()
    {
        b2PolygonShape box;
        vec3 scale = m_pGameObject->GetTransformComponent()->m_scale;
        vec2 size = vec2(scale.x, scale.y);
        box.SetAsBox(size.x / 2, size.y / 2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 1.0f;
        m_pBox2DBody->CreateFixture(&fixtureDef);
    }

    void PhysicsComponent::SetBox(vec2 scale)
    {
        b2PolygonShape box;

        box.SetAsBox(scale.x / 2, scale.y / 2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 1.0f;

        m_pBox2DBody->CreateFixture(&fixtureDef);
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

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicPolygon;
        fixtureDef.density = 1.0f;
        m_pBox2DBody->CreateFixture(&fixtureDef);

    }
    void PhysicsComponent::SetSensor()
    {
        b2CircleShape circle;
        circle.m_radius = m_pGameObject->GetTransformComponent()->m_scale.x * 2;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        fixtureDef.density = 1.0f;
        fixtureDef.isSensor = true;
        m_pBox2DBody->CreateFixture(&fixtureDef);
    }

    void PhysicsComponent::SetLineCensor()
    {
        b2PolygonShape box;
        vec3 scale = m_pGameObject->GetTransformComponent()->m_scale;
        vec2 size = vec2(scale.x, scale.y);
        box.SetAsBox(size.x, size.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 1.0f;
        fixtureDef.isSensor = true;
        m_pBox2DBody->CreateFixture(&fixtureDef);
    }

    void PhysicsComponent::SetRestitution(float restitution)
    {
        if (m_pJoltBody)
        {
            m_pJoltBody->SetRestitution(restitution);
        }
    }

    void PhysicsComponent::SetFriction(float friction)
    {
        if (m_pJoltBody)
        {
            m_pJoltBody->SetFriction(friction);
        }
    }

    void PhysicsComponent::CreateWeldJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor)
    {
        b2WeldJointDef jointDef;
        jointDef.bodyA = m_pBox2DBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBox2DBody;
        jointDef.localAnchorA = b2Vec2(thisObjectAnchor.x, thisObjectAnchor.y);
        jointDef.localAnchorB = b2Vec2(otherObjectAnchor.x, otherObjectAnchor.y);
        jointDef.collideConnected = false;
        m_pBox2DWorld->CreateJoint(&jointDef);
    }
    vec3 PhysicsComponent::GetVelocity()
    {
        return (m_mode == PhysicsLibrary::Box2D) ? vec3(m_pBox2DBody->GetLinearVelocity().x, m_pBox2DBody->GetLinearVelocity().y, 0.0f) : vec3(m_pJoltBody->GetLinearVelocity().GetX(), m_pJoltBody->GetLinearVelocity().GetY(), m_pJoltBody->GetLinearVelocity().GetZ());
    }
}