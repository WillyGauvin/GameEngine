#pragma once

#include "CoreHeaders.h"
#include "Math/Matrix.h"
#include "Component.h"
#include "Physics/Jolt/JoltHelpers.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"

namespace fw
{

	enum class PhysicsCategories
	{
		PhysicsCategory_Default = 1 << 0,
		PhysicsCategory_Wall = 1 << 1,
		PhysicsCategory_Bumper  = 1 << 2,
		PhysicsCategory_Paddle = 1 << 3,
		PhysicsCategory_RedBall = 1 << 4,
		PhysicsCategory_BlueBall = 1 << 5,
		PhysicsCategory_GreenBall = 1 << 6,
		PhysicsCategory_Sensor = 1 << 7,
		PhysicsCategory_RedObstacle = 1 << 8,
		PhysicsCategory_BlueObstacle = 1 << 9,
		PhysicsCategory_GreenObstacle = 1 << 10,

	};


	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic);
		PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic, fw::PhysicsCategories category);

		virtual ~PhysicsComponent();


		void AddLinearImpulse(vec2 impulse);
		void AddAngularImpulse(float impulse);
		void AddForce(vec2 force);

		bool isEnabled() { return m_MotorEnabled; }

		void UpdateBody();

		void SetCircle(bool isProjectile);
		void SetBox();
		void SetPoly(const b2Vec2* points, int32 count);
		void SetSensor();


		//Joints
		void CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor, float UpperLimit, float LowerLimit, float motorSpeed, float motorTorque);
		void CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor, float UpperLimit, float LowerLimit);
		void CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor);

		void CreatePrismaticJoint(GameObject* otherObject, bool collideConnectd, float upperLimit, float lowerLimit, float motorSpeed, float maxMotorForce, bool isMotorEnabled);

		void CreateGearJoint(GameObject* object1, GameObject* object2, float ratio);

		static const char* GetStaticType() { return "PhysicsComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }


		template <class b2Joint>
		void EnableMotor(bool flag)
		{
			int i = 0;
			assert(dynamic_cast<b2Joint*>(m_pJoint));
			if (b2Joint* pJoint = static_cast<b2Joint*>(m_pJoint))
			{
				pJoint->EnableMotor(!pJoint->IsMotorEnabled());
				m_MotorEnabled = flag;
			}
		}

	public:
		b2World* m_pWorld = nullptr;
		b2Body* m_pBody = nullptr;
		b2FixtureDef m_fixtureDef;
		b2Joint* m_pJoint = nullptr;
		bool m_MotorEnabled = false;

	};
}