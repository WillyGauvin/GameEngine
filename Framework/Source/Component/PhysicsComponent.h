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
		None,
		Box2D,
		Jolt,
	};

	enum class ForceMode
	{
		Force,
		Impulse,
	};

	enum class ShapeType
	{
		//2D Shapes
		Square,
		Circle,
		Triangle,
		//3D Shapes
		Cube,
		Sphere,
		Mesh,
	};

	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(PhysicsLibrary libType, GameObject* pGameObject, ShapeType type, bool isDynamic = true, bool isTrigger = false);

		void SetMask(uint16 profile, uint16 mask);

		virtual ~PhysicsComponent();
		
		void Reset();

		void AddForce(vec2 force, ForceMode forceMode = ForceMode::Force);
		void AddForce(vec3 force, ForceMode forceMode = ForceMode::Force);

		void AddUpForce(float force);
		void AddUpForce(float force, vec2 offset);


		void AddForceAtPosition(vec2 force, vec2 pos, ForceMode forceMode = ForceMode::Force);
		void AddForceAtPosition(vec3 force, vec2 pos, ForceMode forceMode = ForceMode::Force);

		void AddTorque(vec3 torque, ForceMode forceMode = ForceMode::Force);

		void UpdateBody();

		void SetCircle(bool isProjectile);
		void SetBox();
		void SetBox(vec2 scale);
		void SetTriangle();
		void SetSensor();
		void SetLineCensor();

		void SetRestitution(float restitution);
		void SetFriction(float friction);


		void CreateWeldJoint(GameObject* otherObject, vec2 thisObjectAnchor, vec2 otherObjectAnchor);



		static const char* GetStaticType() { return "PhysicsComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }
		vec3 GetVelocity();

	private:
		b2World* m_pBox2DWorld = nullptr;
		b2Body* m_pBox2DBody = nullptr;

		JoltWorldBundle* m_pJoltWorld = nullptr;
		JPH::Body* m_pJoltBody = nullptr;

		PhysicsLibrary m_mode;
	};
}