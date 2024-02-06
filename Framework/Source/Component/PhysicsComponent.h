#pragma once

#include "CoreHeaders.h"
#include "Math/Matrix.h"
#include "Component.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"

namespace fw
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(GameObject* pGameObject, b2World* pWorld, bool isDynamic);
		virtual ~PhysicsComponent();

		void UpdateBody();

		void SetCircle(float radius);
		void SetBox(vec2 size);
		void SetPoly(const b2Vec2* points, int32 count);

		static const char* GetStaticType() { return "PhysicsComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }


	public:
		b2World* m_pWorld = nullptr;
		b2Body* m_pBody = nullptr;

	};
}