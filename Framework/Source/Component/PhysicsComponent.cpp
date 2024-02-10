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


        switch (m_pGameObject->GetCollisionCategory())
        {
             case(PhysicsCategories::PhysicsCategory_Default):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Default);

                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Default);
                 break;
             }
             case(PhysicsCategories::PhysicsCategory_Wall):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Wall);
                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);
                 break;

             }
             case(PhysicsCategories::PhysicsCategory_Bumper):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Bumper);
                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);
                 break;

             }
             case(PhysicsCategories::PhysicsCategory_Paddle):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Paddle);
                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);
                 break;

             }
             case(PhysicsCategories::PhysicsCategory_Ball):
             {
                 m_fixtureDef.filter.categoryBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);
                 m_fixtureDef.filter.maskBits = static_cast<uint16>(PhysicsCategories::PhysicsCategory_Wall) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Bumper) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Paddle) | static_cast<uint16>(PhysicsCategories::PhysicsCategory_Ball);

                 break;

             }
        }
	}

	PhysicsComponent::~PhysicsComponent()
	{

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

    void PhysicsComponent::UpdateBody()
    {
        vec3 rotation = vec3(0,0,-1.0 * radsToDegrees(m_pBody->GetAngle()));
        vec3 position = vec3(m_pBody->GetTransform().p.x, m_pBody->GetTransform().p.y, 0);
        m_pGameObject->GetTransformComponent()->UpdatePosition(position);
        m_pGameObject->GetTransformComponent()->UpdateRotation(rotation);
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
        // Create the actual joint in the world

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

        // Initialize the joint definition manually
        jointDef.bodyA = m_pBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBody;
        jointDef.localAnchorA = b2Vec2(thisObjectAnchor.x, thisObjectAnchor.y);
        jointDef.localAnchorB = b2Vec2(otherObjectAnchor.x, otherObjectAnchor.y);
      
        jointDef.enableLimit = true;
        jointDef.lowerAngle = LowerLimit;
        jointDef.upperAngle = UpperLimit;
        // Create the actual joint in the world

        // Initialize the motor on the joint
        jointDef.enableMotor = true;
        jointDef.motorSpeed = 2; // positive values will go counter-clockwise, negative clockwise
        jointDef.maxMotorTorque = 5;





        b2Joint* joint = m_pWorld->CreateJoint(&jointDef);

        b2RevoluteJoint* revJoint = static_cast<b2RevoluteJoint*>(joint);
        
    }


    void PhysicsComponent::CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor)
    {
        // Declare a joint definition object
        b2RevoluteJointDef jointDef;

        jointDef.enableMotor = true;
        // Initialize the joint definition manually
        jointDef.bodyA = m_pBody;
        jointDef.bodyB = otherObject->GetPhysicsComponent()->m_pBody;
        jointDef.localAnchorA = b2Vec2(thisObjectAnchor.x, thisObjectAnchor.y);
        jointDef.localAnchorB = b2Vec2(otherObjectAnchor.x, otherObjectAnchor.y);

        // Create the actual joint in the world
        m_pWorld->CreateJoint(&jointDef);
    }
}