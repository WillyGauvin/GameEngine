#pragma once

#include "CoreHeaders.h"
#include "Math/Matrix.h"
#include "Component.h"
#include "Physics/Jolt/JoltHelpers.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"

namespace fw
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic);
		PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic, uint16 collisionProfile, uint16 collisionProfileMask);

		virtual ~PhysicsComponent();
		
		void Reset();

		void AddLinearImpulse(vec2 impulse);
		void AddAngularImpulse(float impulse);
		void AddForce(vec2 force);
		void AddForce(vec2 force, vec2 offset);
		void AddUpForce(float force, vec2 offset);
		void AddUpForce(float force);


		bool isEnabled() { return m_MotorEnabled; }

		void UpdateBody();

		void SetCircle(bool isProjectile);
		void SetBox();
		void SetBox(vec2 scale);
		void SetPoly(const b2Vec2* points, int32 count);
		void SetTriangle();
		void SetSensor();
		void SetLineCensor();
		void DestoryJoint();

		//Joints
		void CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor, float UpperLimit, float LowerLimit, float motorSpeed, float motorTorque);
		void CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor, float UpperLimit, float LowerLimit);
		void CreateRevolutionJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor);
		void CreateRevolutionJoint(GameObject* otherObject);

		void CreateWeldJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor);

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
		vec2 UpVector = (0.0f,1.0f);
	};
}