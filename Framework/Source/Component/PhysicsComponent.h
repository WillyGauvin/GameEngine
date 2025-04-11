#pragma once

#include "CoreHeaders.h"
#include "Math/Matrix.h"
#include "Component.h"
#include "Physics/Jolt/JoltHelpers.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"

namespace fw
{
	enum class PhysicsLibrary
	{
		Box2D,
		Jolt,
	};

	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(PhysicsLibrary libType, GameObject* pGameObject, bool isDynamic = true);

		void SetMask(uint16 profile, uint16 mask);

		virtual ~PhysicsComponent();
		
		void Reset();

		void AddLinearImpulse(vec2 impulse);
		void AddAngularImpulse(float impulse);
		void AddForce(vec2 force);
		void AddForce(vec2 force, vec2 offset);
		void AddUpForce(float force, vec2 offset);
		void AddUpForce(float force);

		void UpdateBody();

		void SetCircle(bool isProjectile);
		void SetBox();
		void SetBox(vec2 scale);
		void SetPoly(const b2Vec2* points, int32 count);
		void SetTriangle();
		void SetSensor();
		void SetLineCensor();


		void CreateWeldJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor);

		static const char* GetStaticType() { return "PhysicsComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }


	private:
		b2World* m_pBox2DWorld = nullptr;
		b2Body* m_pBox2DBody = nullptr;

		JoltWorldBundle* m_pJoltWorld = nullptr;
		JPH::Body* m_pJoltBody = nullptr;


	private: 
	};
}