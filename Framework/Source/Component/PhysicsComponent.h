#pragma once

#include "CoreHeaders.h"
#include "Math/Matrix.h"
#include "Component.h"

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
		PhysicsCategory_Ball = 1 << 4,
		//PhysicsCategory_Monkey = 1 << 5,
		//PhysicsCategory_Dishwasher = 1 << 6,
	};


	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic, PhysicsCategories PhysicsCategory);
		virtual ~PhysicsComponent();

		void UpdateBody();

		void SetCircle();
		void SetBox();
		void SetPoly(const b2Vec2* points, int32 count);

		static const char* GetStaticType() { return "PhysicsComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }


	public:
		b2World* m_pWorld = nullptr;
		b2Body* m_pBody = nullptr;
		b2FixtureDef m_fixtureDef;

	};
}