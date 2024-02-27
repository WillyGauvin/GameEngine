#include "PhysicsComponent.h"
#include "Component/TransformComponent.h"
namespace fw
{
    PhysicsComponent::PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic) : Component(pGameObject),
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
        bodyDef.angle = -1.0f * degreesToRads(m_pGameObject->GetTransformComponent()->m_rotation.z);
        
        m_pBody = m_pWorld->CreateBody(&bodyDef);
        m_pBody->GetUserData().pGameObject = pGameObject;
	}

    PhysicsComponent::PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic, uint16 collisionProfile, uint16 collisionProfileMask) : Component(pGameObject),
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
        bodyDef.angle = -1.0f * degreesToRads(m_pGameObject->GetTransformComponent()->m_rotation.z);

        m_pBody = m_pWorld->CreateBody(&bodyDef);
        m_pBody->GetUserData().pGameObject = pGameObject;

        m_fixtureDef.filter.categoryBits = collisionProfile;
        m_fixtureDef.filter.maskBits = collisionProfileMask;
    }

	PhysicsComponent::~PhysicsComponent()
	{
	}

    void PhysicsComponent::Reset()
    {
        m_pBody->SetAngularVelocity(0.0f);
        m_pBody->SetLinearVelocity(b2Vec2(0,0));
        b2Vec2 position = b2Vec2(m_pGameObject->GetTransformComponent()->m_position.x, m_pGameObject->GetTransformComponent()->m_position.y);
        float rotation = -1.0 * degreesToRads(m_pGameObject->GetTransformComponent()->m_rotation.z);

        m_pBody->SetTransform(position, rotation);
    }

    void PhysicsComponent::AddLinearImpulse(vec2 impulse)
    {
        assert(m_pBody);
        m_pBody->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), m_pBody->GetWorldCenter(), true);
    }

    void PhysicsComponent::AddAngularImpulse(float impulse)
    {
        m_pBody->ApplyAngularImpulse(impulse, true);
    }

    void PhysicsComponent::AddForce(vec2 force)
    {
        m_pBody->ApplyForce(b2Vec2(force.x, force.y), m_pBody->GetWorldCenter(), true);
    }

    void PhysicsComponent::AddForce(vec2 force, vec2 offset)
    {
        m_pBody->ApplyForce(b2Vec2(force.x, force.y), m_pBody->GetWorldCenter() + b2Vec2(offset.x, offset.y), true);
    }

    void PhysicsComponent::AddUpForce(float force, vec2 offset)
    {
        UpVector = vec2(cos(m_pBody->GetAngle() + PI/2), sin(m_pBody->GetAngle() + PI/2)).Normalize();
        m_pBody->ApplyForce(b2Vec2(UpVector.x * force, UpVector.y * force), m_pBody->GetWorldCenter() + b2Vec2(offset.x, offset.y), true);
    }

    void PhysicsComponent::AddUpForce(float force)
    {
        UpVector = vec2(cos(m_pBody->GetAngle() + PI/2), sin(m_pBody->GetAngle() + PI/2)).Normalize();
        m_pBody->ApplyForce(b2Vec2(UpVector.x * force, UpVector.y * force), m_pBody->GetWorldCenter(), true);
    }

    void PhysicsComponent::UpdateBody()
    {
        vec3 rotation = vec3(0.0f,0.0f,-1.0f * radsToDegrees(m_pBody->GetAngle()));
        vec3 position = vec3(m_pBody->GetTransform().p.x, m_pBody->GetTransform().p.y, 0.0f);
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
    void PhysicsComponent::CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor, float UpperLimit, float LowerLimit, float motorSpeed, float motorTorque)
    {
        // Declare a joint definition object
        b2RevoluteJointDef jointDef;

        // Initialize the joint definition manually
        jointDef.bodyA = m_pBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBody;
        jointDef.localAnchorA = b2Vec2(thisObjectAnchor.x, thisObjectAnchor.y);
        jointDef.localAnchorB = b2Vec2(otherObjectAnchor.x, otherObjectAnchor.y);

        jointDef.enableLimit = true;
        jointDef.lowerAngle = LowerLimit;
        jointDef.upperAngle = UpperLimit;

        // Initialize the motor on the joint
        jointDef.enableMotor = false;
        jointDef.motorSpeed = motorSpeed; // positive values will go counter-clockwise, negative clockwise
        jointDef.maxMotorTorque = motorTorque;

        m_pJoint = m_pWorld->CreateJoint(&jointDef);
    }
    void PhysicsComponent::CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor, float UpperLimit, float LowerLimit)
    {
        // Declare a joint definition object
        b2RevoluteJointDef jointDef;

        jointDef.bodyA = m_pBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBody;
        jointDef.localAnchorA = b2Vec2(thisObjectAnchor.x, thisObjectAnchor.y);
        jointDef.localAnchorB = b2Vec2(otherObjectAnchor.x, otherObjectAnchor.y);
      
        jointDef.enableLimit = true;
        jointDef.lowerAngle = LowerLimit;
        jointDef.upperAngle = UpperLimit;


        jointDef.enableMotor = true;
        jointDef.motorSpeed = 2; // positive values will go counter-clockwise, negative clockwise
        jointDef.maxMotorTorque = 5;

        m_pJoint = m_pWorld->CreateJoint(&jointDef);

        
    }


    void PhysicsComponent::CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor)
    {
        // Declare a joint definition object
        b2RevoluteJointDef jointDef;

        jointDef.enableMotor = true;

        jointDef.bodyA = m_pBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBody;
        jointDef.localAnchorA = b2Vec2(thisObjectAnchor.x, thisObjectAnchor.y);
        jointDef.localAnchorB = b2Vec2(otherObjectAnchor.x, otherObjectAnchor.y);

        m_pJoint = m_pWorld->CreateJoint(&jointDef);
    }

    void PhysicsComponent::CreateRevolutionJoint(GameObject* otherObject)
    {
        // Declare a joint definition object
        b2RevoluteJointDef jointDef;

        jointDef.bodyA = m_pBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBody;
        jointDef.Initialize(jointDef.bodyA, jointDef.bodyB, b2Vec2(otherObject->GetTransformComponent()->m_position.x, otherObject->GetTransformComponent()->m_position.y));

        m_pJoint = m_pWorld->CreateJoint(&jointDef);
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


    void PhysicsComponent::CreatePrismaticJoint(GameObject* otherObject, bool collideConnectd, float upperLimit, float lowerLimit, float motorSpeed, float maxMotorForce, bool isMotorEnabled)
    {
        b2PrismaticJointDef jointDef;
        
        jointDef.enableMotor = isMotorEnabled;

        jointDef.bodyA = m_pBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBody;

        jointDef.enableLimit = true;
        jointDef.upperTranslation = upperLimit;
        jointDef.lowerTranslation = lowerLimit;

        jointDef.motorSpeed = motorSpeed;
        jointDef.maxMotorForce = maxMotorForce;

       
        m_pJoint = m_pWorld->CreateJoint(&jointDef);

        
    }
    void PhysicsComponent::CreateGearJoint(GameObject* object1, GameObject* object2, float ratio)
    {
        b2GearJointDef jointDef;

        jointDef.joint1 = object1->GetPhysicsComponent()->m_pJoint;
        jointDef.joint2 = object2->GetPhysicsComponent()->m_pJoint;
        jointDef.bodyA = object1->GetPhysicsComponent()->m_pBody;
        jointDef.bodyB = object2->GetPhysicsComponent()->m_pBody;

        jointDef.ratio = ratio;

        m_pJoint = m_pWorld->CreateJoint(&jointDef);

    }
}